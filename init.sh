#!/bin/bash

conf_file="pkg.config"
pkg_url="https://gitlab.com/Misuzu-star/deps/-/raw/main"
lib_dir="deps"
pkgs_dir="deps/pkg"

pkgs=()
miss_pkgs=()

read_config(){
    while read line
    do
        if [ ! -z ${line} ]; then
            pkgs[${#pkgs[*]}]=${line}
        fi
    done < ${conf_file}
}

check_lib(){
    echo "==================== check library ===================="
    for p in ${pkgs[*]}
    do
        printf "checking library \e[36m%-26s\e[0m" "[${p}]"
        needtar="0"
        if [ -d "${lib_dir}/${p}/include" ] && [ -d "${lib_dir}/${p}/lib" ]; then
            inc=`ls ${lib_dir}/${p}/include | wc -w`
            libc=`ls ${lib_dir}/${p}/lib | wc -w`
            if [ ${inc} -gt "0" ] || [ ${libc} -gt "0" ]; then
                printf "\e[32m%12s\e[0m\n" "[exsit]"
            else
                needtar="1"
            fi
        else
            needtar="1"
        fi

        if [ ${needtar} -eq "1" ]; then
            if [ -f ${pkgs_dir}/${p}.tar.gz ]; then
                tar -xzf ${pkgs_dir}/${p}.tar.gz -C ${lib_dir}
                printf "\e[33m%12s\e[0m\n" "[reinstall]"
            else
                printf "\e[31m%12s\e[0m\n" "[missing]"
                miss_pkgs[${#miss_pkgs[*]}]=${p}
            fi
        fi
    done
    echo ""
}

download(){
    if [ -z ${miss_pkgs} ]; then
        return
    fi
    mkdir -p ${pkgs_dir}

    echo "================= downloading package ================="
    for file in ${miss_pkgs[*]}
    do
        printf "downloading .... \e[36m%-28s\e[0m" "[${file}]"
        `wget -t 3 -nv -N -P ${pkgs_dir} ${pkg_dir} ${pkg_url}/${file}.tar.gz -o /tmp/wget.log`
        err=`cat /tmp/wget.log | grep ERROR | wc -w`
        if [ ${err} -eq "0" ]; then
            tar -xzf ${pkgs_dir}/${file}.tar.gz -C ${lib_dir}
            printf "\e[32m%10s\e[0m\n" "[OK]"
        else
            printf "\e[31m%10s\e[0m\n" "[failed]"
        fi
    done
    echo ""
    rm -f /tmp/wget.log
}

read_config
check_lib
download
