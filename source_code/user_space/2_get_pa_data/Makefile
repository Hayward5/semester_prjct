CC = gcc
project_name = get_data_fm_physical_add
Program = $(project_name)
Source = $(project_name).c
Object = $(project_name).o

All: $(Program)

$(Object): $(Source)
	$(CC) -c $(Source)

$(Program): $(Object)
	$(CC) -o $(Program) $(Object) 
	make clean
	@echo " "
	@echo "< --- Build [ $(Program) ] Success --- >"
	@echo " "

clean:
	rm ./*.o