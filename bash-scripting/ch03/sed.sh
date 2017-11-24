# sed lets you perform editing as a filter
# ideal for batch editing
# applies editing to all lines of file

# sed substitution can substitute strings
# sed doesn't change the file but outputs the change
sed 's/old/new/' myfile

# multiple substitution (and regex) commands
sed -e 's/[Xx]/Y' -e 's/b.*n/blue/'

# -n only prints what you tell it to now
sed -f sedscript -n sed4 # input file is sed4

# pipe date into sed and substitute characters 
date | sed 's/J/j/'`
sed '1,5p'


