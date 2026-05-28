#!/bin/sh

set -eu

output_dir="result"
model="ywjc"

mkdir -p "$output_dir"

detect_one() {
    image="$1"
    [ -f "$image" ] || return 1

    name="${image%.*}"
    output="$output_dir/${name}_result.jpg"

    echo "detecting $image -> $output"
    detection "$image" "$output" "$model"
    return 0
}

found=0

if [ "$#" -eq 0 ]; then
    set -- blueplat
fi

last=""
for arg in "$@"; do
    last="$arg"
done

if [ "$#" -gt 1 ] && [ ! -f "$last" ]; then
    model="$last"
    total=$(($# - 1))
else
    total=$#
fi

i=1
for input in "$@"; do
    if [ "$i" -gt "$total" ]; then
        break
    fi

    if [ -f "$input" ]; then
        if detect_one "$input"; then
            found=1
        fi
    else
        case "$input" in
            *'*'*|*'?'*|*'['*)
                pattern="$input"
                ;;
            *)
                pattern="${input}*.jpg"
                ;;
        esac

        for image in $pattern; do
            if detect_one "$image"; then
                found=1
            fi
        done
    fi

    i=$(($i + 1))
done

if [ "$found" -eq 0 ]; then
    echo "no images matched" >&2
    exit 1
fi
