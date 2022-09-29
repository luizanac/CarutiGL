#ifndef CARUTIGL_RESULT_HPP
#define CARUTIGL_RESULT_HPP

namespace Caruti {

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

        T &getData() {
            return _data;
        }

        [[nodiscard]] EResultStatus GetStatus() const {
            return _status;
        }
    };
}
#endif //CARUTIGL_RESULT_HPP
