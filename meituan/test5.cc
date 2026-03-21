// test5.cc — 与 test4 同题；大数据（n,m ~ 1e5）版：树链剖分 + 线段树 + 大整数。
// test4.cc 保持不动时，可单独编译本文件。

#include <bits/stdc++.h>
using namespace std;

// ---------- 大整数：二进制 limb（小端），支持 << k、+=、按位全反（长度 len 内）----------
struct BigBin {
    using u32 = uint32_t;
    vector<u32> a;  // a[i] 为第 i 个 32 位块（低位在前）

    static BigBin mask_len(int len) {
        BigBin r;
        if (len == 0) return r;
        int full = len / 32, rem = len % 32;
        r.a.assign(full, ~u32(0));
        if (rem) r.a.push_back((u32(1) << rem) - 1);
        return r;
    }

    void trim() {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }

    // this = this ^ mask（按位异或，mask 与 this 对齐到至少 len 位有效）
    void apply_xor_mask(const BigBin& mask) {
        size_t n = max(a.size(), mask.a.size());
        a.resize(n, 0);
        for (size_t i = 0; i < mask.a.size(); ++i) a[i] ^= mask.a[i];
        trim();
    }

    void shl_bits(int k) {
        if (k == 0 || (a.empty() && k == 0)) return;
        int word = k / 32, rem = k % 32;
        if (rem == 0) {
            a.insert(a.begin(), word, 0);
            return;
        }
        vector<u32> b(word, 0);
        u32 hi = 0;
        for (u32 x : a) {
            b.push_back((x << rem) | hi);
            hi = x >> (32 - rem);
        }
        if (hi) b.push_back(hi);
        a.swap(b);
    }

    void add_u64(uint64_t v) {
        if (v == 0) return;
        uint64_t carry = v;
        size_t i = 0;
        for (; carry && i < a.size(); ++i) {
            uint64_t s = (uint64_t)a[i] + carry;
            a[i] = (u32)s;
            carry = s >> 32;
        }
        while (carry) {
            a.push_back((u32)carry);
            carry >>= 32;
        }
    }

    // this = this * 2^sh + add （add < 2^sh）
    void mul_pow2_add(int sh, const BigBin& add) {
        shl_bits(sh);
        size_t n = max(a.size(), add.a.size());
        a.resize(n, 0);
        uint64_t carry = 0;
        for (size_t i = 0; i < n; ++i) {
            uint64_t ai = i < a.size() ? a[i] : 0;
            uint64_t bi = i < add.a.size() ? add.a[i] : 0;
            uint64_t s = ai + bi + carry;
            if (i < a.size()) a[i] = (u32)s;
            else a.push_back((u32)s);
            carry = s >> 32;
        }
        if (carry) a.push_back((u32)carry);
        trim();
    }

    string to_decimal() const {
        if (a.empty()) return "0";
        string s;
        vector<u32> x = a;
        while (!x.empty()) {
            uint64_t rem = 0;
            for (int i = (int)x.size() - 1; i >= 0; --i) {
                uint64_t cur = (rem << 32) | x[i];
                x[i] = (u32)(cur / 10);
                rem = cur % 10;
            }
            s.push_back(char('0' + rem));
            while (!x.empty() && x.back() == 0) x.pop_back();
        }
        reverse(s.begin(), s.end());
        return s;
    }
};

struct Agg {
    BigBin fwd, bwd;
    int len = 0;
};

static Agg combine_fwd(const Agg& L, const Agg& R) {
    Agg out;
    out.len = L.len + R.len;
    out.fwd = L.fwd;
    out.fwd.mul_pow2_add(R.len, R.fwd);
    // bwd: 先读 R 再读 L
    out.bwd = R.bwd;
    out.bwd.mul_pow2_add(L.len, L.bwd);
    return out;
}

static Agg flip_agg(const Agg& t, int len) {
    Agg out = t;
    BigBin m = BigBin::mask_len(len);
    out.fwd.apply_xor_mask(m);
    out.bwd.apply_xor_mask(m);
    return out;
}

// ---------- 树链剖分 + 线段树 ----------
struct HLD {
    int n, cur;
    vector<vector<int>> g;
    vector<int> fa, dep, sz, son, top, dfn, who;

    HLD(int n_) : n(n_), cur(0), g(n + 1), fa(n + 1), dep(n + 1), sz(n + 1),
                  son(n + 1, 0), top(n + 1), dfn(n + 1), who(n + 1) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs1(int u, int p) {
        fa[u] = p;
        dep[u] = dep[p] + 1;
        sz[u] = 1;
        int mx = 0;
        for (int v : g[u]) {
            if (v == p) continue;
            dfs1(v, u);
            sz[u] += sz[v];
            if (sz[v] > mx) mx = sz[v], son[u] = v;
        }
    }

    void dfs2(int u, int t) {
        top[u] = t;
        dfn[u] = ++cur;
        who[cur] = u;
        if (!son[u]) return;
        dfs2(son[u], t);
        for (int v : g[u]) {
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }

    void build(int root = 1) {
        dep[0] = 0;
        dfs1(root, 0);
        dfs2(root, root);
    }
};

struct SegTree {
    int n;
    vector<Agg> tr;
    vector<char> lz;  // 区间翻转懒标记

    SegTree(const vector<int>& val_on_dfn, const HLD& /*h*/) : n((int)val_on_dfn.size() - 1) {
        tr.resize(4 * n + 4);
        lz.assign(4 * n + 4, 0);
        build(1, 1, n, val_on_dfn);
    }

    void pull(int p) {
        tr[p] = combine_fwd(tr[p * 2], tr[p * 2 + 1]);
    }

    void apply_flip(int p) {
        int len = tr[p].len;
        tr[p] = flip_agg(tr[p], len);
        lz[p] ^= 1;
    }

    void push(int p) {
        if (!lz[p]) return;
        apply_flip(p * 2);
        apply_flip(p * 2 + 1);
        lz[p] = 0;
    }

    void build(int p, int l, int r, const vector<int>& val) {
        if (l == r) {
            tr[p].len = 1;
            int bit = val[l] & 1;
            if (bit) {
                tr[p].fwd.add_u64(1);
                tr[p].bwd.add_u64(1);
            }
            return;
        }
        int mid = (l + r) / 2;
        build(p * 2, l, mid, val);
        build(p * 2 + 1, mid + 1, r, val);
        pull(p);
    }

    void range_flip(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            apply_flip(p);
            return;
        }
        push(p);
        int mid = (l + r) / 2;
        if (ql <= mid) range_flip(p * 2, l, mid, ql, qr);
        if (qr > mid) range_flip(p * 2 + 1, mid + 1, r, ql, qr);
        pull(p);
    }

    Agg range_query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[p];
        push(p);
        int mid = (l + r) / 2;
        if (qr <= mid) return range_query(p * 2, l, mid, ql, qr);
        if (ql > mid) return range_query(p * 2 + 1, mid + 1, r, ql, qr);
        Agg L = range_query(p * 2, l, mid, ql, qr);
        Agg R = range_query(p * 2 + 1, mid + 1, r, ql, qr);
        return combine_fwd(L, R);
    }

    void flip(int l, int r) { range_flip(1, 1, n, l, r); }
    Agg query(int l, int r) { return range_query(1, 1, n, l, r); }
};

struct LCAJump {
    int n, L;
    vector<int> dep;
    vector<vector<int>> up;

    LCAJump(const HLD& h) : n(h.n) {
        dep = h.dep;
        L = 1;
        while ((1 << L) <= n) ++L;
        up.assign(L, vector<int>(n + 1));
        for (int v = 1; v <= n; ++v) up[0][v] = h.fa[v];
        for (int k = 1; k < L; ++k)
            for (int v = 1; v <= n; ++v) up[k][v] = up[k - 1][up[k - 1][v]];
    }

    int lca(int u, int v) const {
        if (dep[u] < dep[v]) swap(u, v);
        int diff = dep[u] - dep[v];
        for (int k = 0; diff; ++k, diff >>= 1)
            if (diff & 1) u = up[k][u];
        if (u == v) return u;
        for (int k = L - 1; k >= 0; --k) {
            if (up[k][u] != up[k][v]) u = up[k][u], v = up[k][v];
        }
        return up[0][u];
    }

    int kth_ancestor(int u, int k) const {
        for (int i = 0; k; ++i, k >>= 1)
            if (k & 1) u = up[i][u];
        return u;
    }
};

static void path_flip(SegTree& seg, HLD& h, int u, int v) {
    while (h.top[u] != h.top[v]) {
        if (h.dep[h.top[u]] < h.dep[h.top[v]]) swap(u, v);
        seg.flip(h.dfn[h.top[u]], h.dfn[u]);
        u = h.fa[h.top[u]];
    }
    if (h.dep[u] > h.dep[v]) swap(u, v);
    seg.flip(h.dfn[u], h.dfn[v]);
}

// u 到 v 的有向路径（u -> v）的十进制值：先 u 一侧到 lca（沿链自下而上），再 lca 到 v（自上而下）
static Agg path_value_query(SegTree& seg, HLD& h, const LCAJump& lj, int u, int v) {
    int w = lj.lca(u, v);
    Agg res;
    res.len = 0;

    auto chain_bwd = [&](int x, int anc) {
        // x 沿重链上到 anc（含两端），在 dfn 上为从 dfn[anc] 到 dfn[x] 的正序，路径方向为 x..anc 即 dfn 递减
        while (true) {
            int top = h.top[x];
            if (h.dep[top] <= h.dep[anc]) {
                int L = h.dfn[anc], R = h.dfn[x];
                Agg mid = seg.query(L, R);
                // 需要 x -> anc 顺序 = dfn 从大到小，即 mid 的 bwd
                Agg part;
                part.len = mid.len;
                part.fwd = std::move(mid.bwd);
                part.bwd = std::move(mid.fwd);
                if (res.len == 0) res = std::move(part);
                else {
                    res.fwd.mul_pow2_add(part.len, part.fwd);
                    BigBin nb = part.bwd;
                    nb.mul_pow2_add(res.len, res.bwd);
                    res.bwd = std::move(nb);
                    res.len += part.len;
                }
                break;
            }
            int L = h.dfn[top], R = h.dfn[x];
            Agg mid = seg.query(L, R);
            Agg part;
            part.len = mid.len;
            part.fwd = std::move(mid.bwd);
            part.bwd = std::move(mid.fwd);
            if (res.len == 0) res = std::move(part);
            else {
                res.fwd.mul_pow2_add(part.len, part.fwd);
                BigBin nb = part.bwd;
                nb.mul_pow2_add(res.len, res.bwd);
                res.bwd = std::move(nb);
                res.len += part.len;
            }
            x = h.fa[top];
        }
    };

    auto chain_fwd = [&](int x, int anc) {
        // 从 anc 沿树走到 x，dfn 沿重链可能多段；需按 anc -> x 顺序
        vector<pair<int, int>> segs;  // [L,R] on dfn, 每段重链上沿深度递增 = dfn 区间
        int t = x;
        while (true) {
            int top = h.top[t];
            if (h.dep[top] <= h.dep[anc]) {
                segs.push_back({h.dfn[anc], h.dfn[t]});
                break;
            }
            segs.push_back({h.dfn[top], h.dfn[t]});
            t = h.fa[top];
        }
        reverse(segs.begin(), segs.end());
        for (auto [L, R] : segs) {
            Agg mid = seg.query(L, R);
            if (res.len == 0) {
                res = std::move(mid);
                continue;
            }
            res.fwd.mul_pow2_add(mid.len, mid.fwd);
            BigBin nb = mid.bwd;
            nb.mul_pow2_add(res.len, res.bwd);
            res.bwd = std::move(nb);
            res.len += mid.len;
        }
    };

    if (u == w) {
        chain_fwd(v, w);
        return res;
    }
    if (v == w) {
        chain_bwd(u, w);
        return res;
    }
    chain_bwd(u, w);
    // 跳过重复的 lca：u 侧已含 w，v 侧从 w 的子节点走向 v
    int child_on_path = lj.kth_ancestor(v, lj.dep[v] - lj.dep[w] - 1);
    chain_fwd(v, child_on_path);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> num(n + 1);
    for (int i = 1; i <= n; ++i) cin >> num[i];

    HLD h(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        h.add_edge(u, v);
    }
    h.build(1);

    vector<int> val(n + 1);
    for (int i = 1; i <= n; ++i) val[h.dfn[i]] = num[i];
    SegTree seg(val, h);
    LCAJump lj(h);

    for (int i = 0; i < m; ++i) {
        int op, u, v;
        cin >> op >> u >> v;
        if (op == 1) {
            path_flip(seg, h, u, v);
        } else {
            Agg ans = path_value_query(seg, h, lj, u, v);
            cout << ans.fwd.to_decimal() << '\n';
        }
    }
}

/*
题意同 test4 注释：
第一行 n,m；第二行 n 个 0/1；n-1 条边；m 次操作。
1：路径上点权翻转；2：有向路径 u->v 上比特组成的十进制值。

本文件：树链剖分 + 线段树（区间翻转懒标记）+ 路径查询合并大整数，面向 n,m ~ 1e5。
小数据可继续用 test4 的 DFS 找路径写法。
*/
