```
场景	推荐封装类
简单独占锁，无需灵活控制	lock_guard
需要手动解锁 / 超时 / 延迟加锁	unique_lock
读写锁的读操作	shared_lock(C++17)
同时锁定多个互斥锁	scoped_lock（C++17）
```

```
特性	std::unique_lock	std::shared_lock
锁类型	独占锁（写锁 / 普通互斥锁）	共享锁（仅读锁，适配 shared_mutex）
适配的锁	所有互斥锁（mutex/timed_mutex/shared_mutex 等）	仅 shared_mutex/shared_timed_mutex
并发特性	同一时间仅一个线程持有	同一时间多个线程可持有
核心用途	写操作、普通独占访问	读操作（读密集场景）
```