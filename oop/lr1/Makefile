SERVER_USER = artem
SERVER_IP = 5.129.251.235
REMOTE_PATH = /home/artem/

push:
	rsync -avz --exclude='Makefile' ./ $(SERVER_USER)@$(SERVER_IP):$(REMOTE_PATH)
