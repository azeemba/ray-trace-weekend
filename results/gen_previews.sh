
cd results
find -name "*.ppm" | xargs -i{} magick convert {} {}.jpg

echo "Previews" > README.md
echo "=======" >> README.md
echo "" >> README.md
echo "" >> README.md


cat readme-header.md > ../README.md

for f in *.jpg
do
  echo "![$f](results/$f)" >> README.md
  echo "" >> README.md

  echo "![$f](results/$f)" >> ../README.md
  echo "" >> ../README.md
done

