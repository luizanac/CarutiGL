//
// Created by Luiz on 17/09/2022.
//

#ifndef CARUTIGL_RESULT_HPP
#define CARUTIGL_RESULT_HPP

enum EStatus {
    Success, Fail
};

template<typename T>
class Result {
private:
    T _data;
    EStatus _status;

public:
    explicit Result(EStatus status) : _status(status) {
        _data = nullptr;
    }

    Result(T data, EStatus status) : _data(data), _status(status) {
    }

    T getData() {
        return _data;
    }

    [[nodiscard]] EStatus getStatus() const {
        return _status;
    }
};

#endif //CARUTIGL_RESULT_HPP
