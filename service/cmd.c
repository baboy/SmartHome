//
//  cmd.c
//  HRC
//
//  Created by baboy on 3/8/14.
//  Copyright (c) 2014 baboy. All rights reserved.
//
#include "cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//|_2_|_2_|__4__|__4__|__4__|__4__|________________|
//pre  ver time   cmd  ctype cmd-len data
void * create_cmd_data(Cmd cmd){
    int len = 20 + cmd.msg_length;
    void *cmd_data = (void*)malloc(len);
    memset(cmd_data, 0, len);
    
    int offset = 0;
    // prefix
    unsigned short prefix = cmd.prefix;
    memcpy(cmd_data+offset, &prefix, 2);
    offset += 2;
    
    
    // version
    unsigned short version = cmd.version;
    memcpy(cmd_data + offset, &version, 2);
    offset += 2;
    
    //timestamp
    int timestamp = cmd.timestamp;
    memcpy(cmd_data + offset, &timestamp, 4);
    offset += 4;
    
    //cmd
    int c = cmd.cmd;
    memcpy(cmd_data + offset, &c, 4);
    offset += 4;
    
    //device
    int device = cmd.device;
    memcpy(cmd_data + offset, &device, 4);
    offset += 4;
    
    
    //msg_length
    int dlen = cmd.msg_length;
    memcpy(cmd_data + offset, &dlen, 4);
    offset += 4;
    
    // data
    memcpy(cmd_data + offset, cmd.msg, dlen);
    return cmd_data;
}

Cmd get_cmd(void *cmd_data){
    Cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    
    int offset = 0;
    // prefix
    unsigned short prefix = 0;
    memcpy(&prefix, cmd_data+offset, 2);
    cmd.prefix = prefix;
    offset += 2;
    
    
    // version
    unsigned short version = 0;
    memcpy(&version, cmd_data+offset, 2);
    cmd.version = version;
    offset += 2;
    
    //timestamp
    int timestamp;
    memcpy(&timestamp, cmd_data+offset, 4);
    cmd.timestamp = timestamp;
    offset += 4;
    
    //cmd
    int c;
    memcpy(&c, cmd_data+offset, 4);
    cmd.cmd = c;
    offset += 4;
    
    //device
    int device ;
    memcpy(&device, cmd_data+offset, 4);
    cmd.device = device;
    offset += 4;
    
    
    //msg_length
    int mlen;
    memcpy(&mlen, cmd_data+offset, 4);
    cmd.msg_length = mlen;
    offset += 4;
    
    // data
    void *d = (void *)malloc(mlen);
    memcpy(d, cmd_data+offset, mlen);
    cmd.msg = d;
    return cmd;
}
void p(Cmd cmd){
	char *msg = (char*) malloc(cmd.msg_length);
	memset(msg,0,cmd.msg_length+1);
	memcpy(msg,cmd.msg,cmd.msg_length);
	printf("Cmd: %u|%u|%d|%d|%d|%d|%s\n", cmd.prefix, cmd.version, cmd.timestamp, cmd.cmd, cmd.device, cmd.msg_length,msg);
	printf("Cmd msg:%x\n", msg);
}

int main(int argc, char argv[]){
	Cmd cmd;
	cmd.prefix = 0xFFFF;
	cmd.version = 1;
	cmd.timestamp = 2;
	cmd.cmd = 3;
	cmd.device = 4;
	cmd.msg_length = 11;
	cmd.msg = "Hello,baboy";
	p(cmd);
	void *d = create_cmd_data(cmd);
	printf("%X\n", d);
	Cmd cmd2 = get_cmd(d);
	p(cmd2);
}
