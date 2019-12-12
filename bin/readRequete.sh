#!/bin/bash

> data/index.dat #Vider le fichier index

for fich in `ls -1 requete/`
do
    if [[ ${fich: -4} == ".xml" || ${fich: -4} == ".wav" || ${fich: -4} == ".bin" || ${fich: -4} == ".bmp" || ${fich: -4} == ".jpg" ]]
    then
        echo $fich >> data/index.dat
    fi
done



exit 0