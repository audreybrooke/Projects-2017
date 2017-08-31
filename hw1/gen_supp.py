import os

target_file = 'gcc.supp'

os.system('cp ' + target_file + ' ~/' + target_file)

if os.path.exists('/home/student/' + target_file):
	os.system('echo "\nSuccesfully generated suppression file."')
	os.system('echo "Add --suppressions=/home/student/' + target_file + ' to the valgrind flags when running valgrind to use this file.\n"')
else:
	os.system('echo "Unable to generate suppression file"')