#include <sys/dir.h>
class Dir{
    public:
        Dir();
        ~Dir();
        void GetPaths(char* input, char* out);
    private:
        DIR * dirp;
        struct direct *d;
};