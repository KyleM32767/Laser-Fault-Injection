#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pdmv5.h"

int main(void)
{
    int i, returnValue;
    float currentMax;
    float currentPercent;
    float current;

   struct sp_port **ports;
   struct sp_port *port;
      
   sp_list_ports(&ports);

    for (i = 0; ports[i]; i++)
    {
        sp_copy_port(ports[i], &port);

        printf("Found port: '%s'.\n", sp_get_port_name(port));
        if(OpenCommunication_PDMv5(sp_get_port_name(port), &port) == SP_OK)
        {
            //The address used is 1, so the second parameter is 1
            int address = 1;
            
            //Read the max current in mA
            returnValue = ReadMaximumCurrent_PDMv5(port, address, &currentMax);
            
            //Read the actual current in percentage of the max current
            returnValue = ReadCurrent_PDMv5(port, address, &currentPercent);
            
            //The current in mA
            current = currentPercent*currentMax/100.;
            
            //Set the current to 70.5% of the max current
            returnValue = SetCurrent_PDMv5(port, address, 70.5);  

            //The current is not yet at 70.5%, there should be a reapplication of the parameters
            returnValue = ApplyRequest_PDMv5(port, address);

            //The current is now applied
            
            //Set the laser to ON
            returnValue = SetLaserStatus_PDMv5(port, address, 1);            
            returnValue = ApplyRequest_PDMv5(port, address);
            
            //The laser is now ON
            
            //Wait 30s
            sleep(30);
            
            //Set the laser to OFF
            returnValue = SetLaserStatus_PDMv5(port, address, 1);
            returnValue = ApplyRequest_PDMv5(port, address);                       
            
            CloseCommunication_PDMv5(port);
        }
        else
        {
            printf("Found no card.\n");
        }
        
        sp_free_port(port);
    }

    sp_free_port_list(ports);

    return 0;
}