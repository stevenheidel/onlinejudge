SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(SELF_DIR)../Makefile

submit: build
	@../../scoreboard.sh ${EXECUTABLE} 2>/dev/null
