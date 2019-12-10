#!/bin/bash

> data/index.dat #Vider le fichier index

i=1
for fich in `ls -1 requete/`
do
    if [[ ${fich: -4} == ".xml" || ${fich: -4} == ".wav" || ${fich: -4} == ".bin" || ${fich: -4} == ".bmp" || ${fich: -4} == ".jpg" ]]
    then
        echo "$i\- $fich" >> data/index.dat
        let "i = i +1"
    fi
done



exit 0