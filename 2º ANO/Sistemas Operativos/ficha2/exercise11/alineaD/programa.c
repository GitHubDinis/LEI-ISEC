#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *vars[] = {
        "PATH", "HOME", "USER", "SHELL", "LANG", "PWD", "LOGNAME", "TERM", "EDITOR", "HOSTNAME"
    };
    int num_vars = sizeof(vars) / sizeof(vars[0]);

    for (int i = 0; i < num_vars; i++) {
        const char *value = getenv(vars[i]);
        if (value != NULL) {
            printf("%s=%s\n", vars[i], value);
        } else {
            printf("%s is not set\n", vars[i]);
        }
    }
    return 0;
}
