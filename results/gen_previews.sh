
cd results
find -name "*.ppm" | xargs -i{} magick convert {} {}.jpg
