@echo off
title THE Dark Age - The Arcanum Quest
echo Compilando o jogo...
wsl -e bash -c "cd /mnt/c/Users/Dell/Desktop/UFMG/PDS2/PF/PROJETO/PDS2-2026-PF-grupo5 && make clean > /dev/null 2>&1 && make 2>&1 | tail -5 && echo '' && echo 'Iniciando...' && sleep 1 && ./bin/The_Dark_Age_-_The_Arcanum_Quest"
pause
