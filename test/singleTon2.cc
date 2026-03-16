class SingleTon {
private:
    SingleTon() = default;
    ~SingleTon() = default;
    SingleTon(const SingleTon&) = delete;
    SingleTon& operator=(const SingleTon&) = delete; 
    SingleTon(SingleTon&&) = delete;
    SingleTon& operator=(SingleTon&&) = delete;

public:
    static SingleTon& getInstance() {
        static SingleTon _instance;
        return _instance;
    }
};