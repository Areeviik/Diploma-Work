# Diploma-Work

Using make will create the shell executable.

Simply run it with  ./shell


---Main instructions---
• Display a prompt when waiting for a new command.
• Have a working history.
• Search and launch the right executable (based on the PATH variable or using a
  relative or an absolute path).
• Implement redirections:
  ◦ < should redirect input.
  ◦ > should redirect output.
  ◦ << should be given a delimiter, then read the input until a line containing the
    delimiter is seen. However, it doesn’t have to update the history!
  ◦ >> should redirect output in append mode.
• Implement pipes (| character). The output of each command in the pipeline is
  connected to the input of the next command via a pipe.
• Handle environment variables ($ followed by a sequence of characters) which
  should expand to their values.
• Handle $? which should expand to the exit status of the most recently executed
  foreground pipeline.
• Handle ctrl-C, ctrl-D and ctrl-\
  ◦ ctrl-C displays a new prompt on a new line.
  ◦ ctrl-D exits the shell.
  ◦ ctrl-\ does nothing.
• Implement the following builtins:
  ◦ echo with option -n
  ◦ cd with only a relative or absolute path
  ◦ pwd with no options
  ◦ export with no options
  ◦ unset with no options
  ◦ env with no options or arguments
  ◦ exit with no options
  
  
  
  
