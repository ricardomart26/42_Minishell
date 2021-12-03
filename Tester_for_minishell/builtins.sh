
confirmation() {
    read -p "Continue?"
    echo
}

echo "=================== echo builtin ======================"

echo "asdioasjdoiajsidojas"
echo adsoaisdjioasjiodjao
echo "sadasijdoasijdias   " "    adsasiduhadisu "
echo 'ioasioajdosiads    sadk'asdasdioj asdjaiosdj
echo "asdasdaosijdioas " "'|'" echo "adeiaoidjaeoijd"
confirmation

echo "=================== cd builtin ======================"

cd
echo "should be home"
pwd
cd desktop
echo "should be desktop"
cd ~
echo "should be home again"
confirmation

echo "===================  builtins ======================"

echo "Env"
env
confirmation

echo "Ordered list"
export
confirmation

echo "Add var to env list"
export var=3
env
confirmation

echo "Remove var"
unset var
env
confirmation
