pwd



cp -rd ../* ./contents

ls -la contents

jb build .

rm -rd ~/html/*
cp -rd ./_build/html/* ~/html

rm -rd contents/*


