#!/system/bin/sh
if [ -r /data/media/0/kbc/cmdline ]; then
    cat /data/media/0/kbc/cmdline > /proc/cmdline
elif [ -r /data/media/0/kbc/felica_key ]; then
    local ORIG_CMDLINE=`cat /proc/cmdline`
    local FELICA_KEY=`head -1 /data/media/0/kbc/felica_key`
    set -- $FELICA_KEY
    local CORDON="cordon=$1"
    local CONNIE="connie=$2"
    echo -n "$CORDON $CONNIE $ORIG_CMDLINE" | sed -e 's/^ +//' > /proc/cmdline
fi
exit 0
