
confirmation() {
    read -p "Continue?"
    echo
}
echo "wc -l"
wc -l
confirmation

echo "ls -la | wc"
ls -la | wc
confirmation

echo "grep as"
grep as
confirmation
