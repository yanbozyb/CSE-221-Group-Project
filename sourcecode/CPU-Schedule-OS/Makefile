run: 
	cd procedure_call; make all; cd ../;
	cd syscall; make syscall; cd ../;
	cd task_creation/fork_test; make fork; cd ../../;
	cd task_creation/pthread_create_test; make pthread; cd ../../;
	cd context_switch; make all; cd ../;

	echo -e "\033[0;32m Running procedure call test\033[0m"
	cd procedure_call; ./pcall; cd ../;
	cd procedure_call; ./rdtscoverhead; cd ../;

	echo -e "\033[0;32m Running syscall test\033[0m"
	cd syscall; ./syscall; cd ../;

	echo -e "\033[0;32m Running task creation test\033[0m"
	cd task_creation/fork_test; ./fork; cd ../../
	cd task_creation/pthread_create_test; ./pthread; cd ../../

	echo -e "\033[0;32m Running context switch test\033[0m"
	cd context_switch; ./context_switch_fork; cd ../
	cd context_switch; ./context_switch_pthread; cd ../

clean:
	cd procedure_call; make clean; cd ../;
	cd syscall; make clean; cd ../;
	cd task_creation/fork_test; make clean; cd ../../;
	cd task_creation/pthread_create_test; make clean; cd ../../;
	cd context_switch; make clean; cd ../;

