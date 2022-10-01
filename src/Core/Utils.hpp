#ifndef CARUTIGL_UTILS_HPP
#define CARUTIGL_UTILS_HPP

class Utils {
public:
    static float Mapf(float value,
                      float start1, float stop1,
                      float start2, float stop2) {
        float outgoing =
                start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));

        return outgoing;
    }

    static int Mapi(int value,
                    int start1, int stop1,
                    int start2, int stop2) {

        return (int) Mapf(value, start1, stop1, start2, stop2);
    }
};


#endif //CARUTIGL_UTILS_HPP
