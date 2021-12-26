

find -name "*.ppm" | xargs -i{} echo magick convert {} {}.jpg
