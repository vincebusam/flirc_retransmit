#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <flirc.h>

#define MAX_CONFIG 128

struct input_event {
    struct timeval time;
    unsigned short type;
    unsigned short code;
    unsigned int value;
};


typedef struct {
    unsigned short code;
    uint16_t buf[100];
    int len;
    char *str;
} keyconfig;


void load_config(keyconfig *config) {
    FILE *fp;
    int count=0, i, buf_size, len;
    char buf[2048], *inkey, *outkey;
    
    memset(config, 0, sizeof(keyconfig) * MAX_CONFIG);
    fp = fopen("config.txt", "r");
    while (fgets(buf, sizeof(buf), fp)) {
        if (buf[0] == '#')
            continue;
        inkey = strtok(buf, " ");
        outkey = strtok(NULL, "\n");
        sscanf(inkey, "%i", &i);
        config[count].code = i;
        config[count].str = strdup(outkey);

        i = 0;
        buf_size = 0;
        len = strlen(outkey);
        while (len > 0) {
            config[count].buf[buf_size++] = strtol(&outkey[i], NULL, 10);
            while (outkey[i++] != ',' && len--);
	}

        config[count].len = buf_size;

        printf("Added code %i\n", config[count].code);
        count += 1;
        if (count >= MAX_CONFIG)
            break;
    }

    fclose(fp);
}


int main(int argc, char *argv[]) {
    int input, len, i;
    keyconfig config[MAX_CONFIG];
    struct input_event ie;

    load_config(config);
    i = fl_open_device(0x20A0, "flirc.tv");
    input = open("/dev/input/by-id/usb-flirc.tv_flirc-if01-event-kbd", O_RDONLY);
    printf("Reading IR input\n");
    while (1) {
        len = read(input, &ie, sizeof(struct input_event));
        printf("Input %i %i %i %i\n", ie.time.tv_sec, ie.type, ie.code, ie.value);
        if (len > 0) {
            for (i=0; i<(sizeof(config)/sizeof(keyconfig)); i++) {
                if (config[i].len == 0)
                    continue;
                if ((config[i].code == ie.code) && (ie.value == 0)) {
                    printf("Matched input %i => %i %s\n", ie.code, config[i].len, config[i].str);
                    len = fl_transmit_raw(config[i].buf, config[i].len, 2300, 3);
                    printf("%i\n", len);
                }
            }
        }
    }
    return 0;
}
