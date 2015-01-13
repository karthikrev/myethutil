#include<Python.h>

#include<sys/ioctl.h>
#include<netinet/in.h>
#include<linux/sockios.h>
#include<linux/if.h>
#include<linux/ethtool.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


int Cgetspeed(char *nic){ 
    int sock;
    struct ifreq ifr;
    struct ethtool_cmd edata;
    int rc;

    // obtain the fd
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    strncpy(ifr.ifr_name, nic, sizeof(ifr.ifr_name));
    ifr.ifr_data = &edata;

    edata.cmd = ETHTOOL_GSET;
    rc = ioctl(sock, SIOCETHTOOL, &ifr);

    return edata.speed;
}


// Python wrapper

//Returns pythonobject pointer
static  PyObject* getspeed(PyObject* self, PyObject* args) {
    char *pyarg;
    if(!PyArg_ParseTuple(args, "s", &pyarg)){
        return NULL; 
    }
    return Py_BuildValue("i", Cgetspeed(pyarg));
}

static PyMethodDef myMethods[] = {
    {"getspeed", getspeed, METH_VARARGS, "Get the nic speed"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initextension(void){
    (void) Py_InitModule("extension", myMethods);
}

