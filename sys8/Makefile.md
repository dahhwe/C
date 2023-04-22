bin_PROGRAMS = client server
client_SOURCES = interface.c client.c
server_SOURCES = server.c logic.c
server_LDADD = -lm