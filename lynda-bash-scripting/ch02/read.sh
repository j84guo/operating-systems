export a=first	
export b=second	
export c=third
echo a is '['$a']' b is '['$b']' c is '['$c']'

#reads first token to a, rest of line to b, c is unchanged
read a b <data_file
echo a is '['$a']' b is '['$b']' c is '['$c']'

