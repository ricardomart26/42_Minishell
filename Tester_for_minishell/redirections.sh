touch filename
echo "teste nmr1" < filename
echo "teste nmr2" << filename
cat > filename
echo "Should be teste nm1\n teste nmr2"
sleep(3)
echo "AGORA FICA VAZIO" < filename
cat filename
sleep(3)
