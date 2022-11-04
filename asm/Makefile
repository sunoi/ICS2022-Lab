NAME := $(shell basename $(PWD))
all: $(NAME)-64
export MODULE := Lab2
include ../Makefile

run: all
	@git commit -a -m "run lab2"
	./$(NAME)-64
