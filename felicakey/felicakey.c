#include <stdlib.h>
#include <string.h>
#include <cutils/properties.h>

#define LOG_TAG "FeliCaKey"
#include <cutils/log.h>

#define FELICAKEY_VALUE_MAX 32
#define PROP_KERNEL_CMDLINE_CORDON "ro.kernel.cmdline.cordon"
#define PROP_KERNEL_CMDLINE_CONNIE "ro.kernel.cmdline.connie"
#define HEAD_KERNEL_CMDLINE_CONNIE "SGH-N075_DCM_JPN_"

bool isvalid_felicakey(const char *felicakey, char *key)
{
    if(strlen(felicakey) != FELICAKEY_VALUE_MAX) {
        ALOGE("%s: invalid length `%s`", key, felicakey);
        return false;
    }

    int i;
    for(i=0; i<strlen(felicakey); i++) {
        if(! isxdigit(felicakey[i])) {
            ALOGE("%s: invalid character", key);
            return false;
        }
    }
    return true;
}

void replace_cordon(char **line)
{
    char propval[PROPERTY_VALUE_MAX];
    const char *startpos, *endpos;
    *propval = '\0';

    do {
        startpos = strstr(*line, "cordon=");
        if (! startpos)
            break;
        startpos += strlen("cordon=");
        endpos = strchr(startpos, ' ');
        if (! endpos)
            endpos = startpos + strlen(startpos);

        if(property_get(PROP_KERNEL_CMDLINE_CORDON, propval, "") <= 0)
            break;
        if(! isvalid_felicakey(propval, "cordon"))
            break;
        if(strlen(propval) != (endpos - startpos))
            break;
        strncpy(*line + (startpos - *line), propval, strlen(propval));

        ALOGI("cordon modified");
    } while(0);
}

void replace_connie(char **line)
{
    size_t hsize;
    hsize = strlen(HEAD_KERNEL_CMDLINE_CONNIE);

    char propval[PROPERTY_VALUE_MAX + hsize];
    const char *startpos, *endpos;
    *propval = '\0';

    do {
        startpos = strstr(*line, "connie=" HEAD_KERNEL_CMDLINE_CONNIE);
        if (! startpos)
            break;
        startpos += strlen("connie=" HEAD_KERNEL_CMDLINE_CONNIE);
        endpos = strchr(startpos, ' ');
        if (! endpos)
            endpos = startpos + strlen(startpos);

        if(property_get(PROP_KERNEL_CMDLINE_CONNIE, propval, "") <= 0)
            break;
        if(strncmp(propval, HEAD_KERNEL_CMDLINE_CONNIE, hsize) == 0) {
            strncpy(propval, propval + hsize, strlen(propval) - hsize);
            propval[strlen(propval) - hsize] = '\0';
        }
        if(! isvalid_felicakey(propval, "connie"))
            break;
        if(strlen(propval) != (endpos - startpos))
            break;
        strncpy(*line + (startpos - *line), propval, strlen(propval));

        ALOGI("connie modified");
    } while(0);
}

void getcmdline(char **line)
{
    char const *proc_cmdline = "/proc/cmdline";
    FILE *fp;
    char buf[1024] = {0};
    size_t buflen, total;
    fp = fopen(proc_cmdline, "r");
    if(fp == NULL)
        exit(EXIT_FAILURE);
    *line = NULL;
    total = 0;
    while(fgets(buf, sizeof(buf), fp) != NULL) {
        buflen = strlen(buf);
        char *tmp = realloc(*line, total + buflen + 1);
        if(tmp == NULL) {
            free(*line);
            break;
        } else {
            *line = tmp;
        }
        strncpy(*line + total, buf, buflen);
        total += buflen;
    }
    fclose(fp);
}

void setcmdline(char **line)
{
    char const *proc_cmdline = "/proc/cmdline";
    FILE *fp;
    fp = fopen(proc_cmdline, "w");
    if(fp == NULL)
        exit(EXIT_FAILURE);
    fputs(*line, fp);
}

int main(int argc, char *argv[])
{
    char *cmdline = {'\0'};
    getcmdline(&cmdline);
    replace_cordon(&cmdline);
    replace_connie(&cmdline);
    setcmdline(&cmdline);
    exit(EXIT_SUCCESS);
}
