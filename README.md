# InventoryKeeper


psuedocode for main()

open partfile.dat
do
	get main menu choice
switch
	case add:		add_record
	case delete:	delete_record
	case change:	change_record
	case display:	display_file
	case quit:		quit program
	default:		display "Wrong Choice, Please Try Again"
endswitch
while( !quit )
close partfile.dat


psuedocode for add_record:

get record number
validate record number
get rest of record data
find record position in file
if record does not exist
	write record onto file
else 
	display "Part Already Exists"
endif		


psuedocode for delete_record:

get record number
validate record number 
find and read record from file
if record position is not occupied
	display "Record does not exist"
else
	delete record from file
endif


psuedocode for change_record:

get record number
validate record 	
find and record from file
if record position is not occupied
	display "Record does not exist"
else 
	display current record contents
do 
	get change menu choice
	switch (change menu choice)
		case change q_o_h: 		get new q_o_h
		case change price: 		get price
		case quit and write:	write changed record onto file
		default:				display "invalid choice"
	endswitch
while (!quit)


psuedocode for display_file

move to start of file
display column headings
for (rec_num = 1; rec_num <= 99; ++rec_num)
	read record
	if record is not empty
		print record
			increment record count
		endif	
	endfor	
print record count


