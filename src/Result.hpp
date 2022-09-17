//
// Created by Luiz on 17/09/2022.
//

#ifndef CARUTIGL_RESULT_HPP
#define CARUTIGL_RESULT_HPP

enum EResultStatus {
    Success, Fail
};

template<typename T>
class Result {
private:
    T _data;
    EResultStatus _status;

public:
    explicit Result(EResultStatus status) : _status(status) {
        _data = nullptr;
    }

    Result(T data, EResultStatus status) : _data(data), _status(status) {
    }

    T getData() {
        return _data;
    }

    [[nodiscard]] EResultStatus getStatus() const {
        return _status;
    }
};

#endif //CARUTIGL_RESULT_HPP
