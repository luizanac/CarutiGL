#ifndef CARUTIGL_RESULT_HPP
#define CARUTIGL_RESULT_HPP

namespace Caruti {

    enum EResultStatus {
        Success, Fail
    };

    template<typename T>
    class Result {
    private:
        T m_Data;
        EResultStatus m_Status;

    public:
        explicit Result(EResultStatus status) : m_Status(status) {
            m_Data = nullptr;
        }

        Result(T data, EResultStatus status) : m_Data(data), m_Status(status) {
        }

        T &getData() {
            return m_Data;
        }

        [[nodiscard]] EResultStatus GetStatus() const {
            return m_Status;
        }
    };
}
#endif //CARUTIGL_RESULT_HPP
