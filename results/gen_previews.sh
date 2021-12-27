
cd results
find -name "*.ppm" | xargs -i{} magick convert {} {}.jpg

echo "Previews" > README.md
echo "=======" >> README.md
echo "" >> README.md
echo "" >> README.md

for f in *.jpg
do
  echo "![$f]($f)" >> README.md
  echo "" >> README.md
done
