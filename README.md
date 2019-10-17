# aureverse

Reverses the audio stored in an AU file.

# Example file

It can be created with this command:

    espeak -v de "hallo welt" --stdout | ffmpeg -f wav -i pipe: hallo.au
    
# Rationale

This was just a challenge if I could do it (in a reasonable time), since I am (currently) not very good at C development. I am glad that I succeeded. :-)
