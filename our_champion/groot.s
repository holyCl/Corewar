.name		"Groot"
.comment	"I am Groot! We are Groot!"

label:	sti r1, %:live, %1
		sti r1, %:copy, %1

copy:	live %1
		fork %:label
		
		and r1, %0, r1
live:	live %1
		zjmp %:live
