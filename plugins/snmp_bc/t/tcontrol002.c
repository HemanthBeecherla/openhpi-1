/* -*- linux-c -*-
 * 
 * (C) Copyright IBM Corp. 2004
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Author(s):
 *     Peter D Phan <pdphan@users.sourceforge.net>
 */


#include <snmp_bc_plugin.h>
#include <sahpimacros.h>
#include <tsetup.h>

int main(int argc, char **argv) 
{

	/* ************************
	 * Local variables
	 * ***********************/	 
	int testfail = 0;
	SaErrorT          err;
	SaErrorT expected_err;

	SaHpiResourceIdT  id;
        SaHpiSessionIdT sessionid;
	 
	SaHpiCtrlNumT cid = 1;
	SaHpiCtrlModeT mode;
	SaHpiCtrlStateT state;
													   
	/* *************************************	 	 
	 * Find a resource with Sensor type rdr
	 * ************************************* */
        struct oh_handler l_handler;
	struct oh_handler *h= &l_handler;
        SaHpiRptEntryT rptentry;
	
	err = tsetup(&sessionid);
	if (err != SA_OK) {
		printf("Error! bc_control, can not setup test environment\n");
		return -1;

	}
	err = tfind_resource(&sessionid, SAHPI_CAPABILITY_CONTROL, h, &rptentry);
	if (err != SA_OK) {
		printf("Error! bc_control, can not find a control resource.");
		err = tcleanup(&sessionid);
		return -1;
	}

	id = rptentry.ResourceId;
	/************************** 
	 * Test 1: Normal get    
	 *************************/
	expected_err = SA_OK;
	err = snmp_bc_get_control_state((void *)h->hnd, id, cid, &mode, &state);
	checkstatus(&err, &expected_err, &testfail);
	
	/************************** 
	 * Test 2: Get with no mode
	 * expected_err = SA_OK;
	 *************************/
	err = snmp_bc_get_control_state((void *)h->hnd, id, cid, NULL, &state);
	checkstatus(&err, &expected_err, &testfail);
	
	/************************** 
	 * Test 3: Get with no state 
	 * expected_err = SA_OK;
	 *************************/
	err = snmp_bc_get_control_state((void *)h->hnd, id, cid, &mode, NULL);
	checkstatus(&err, &expected_err, &testfail);
	
	/***************************
	 * Cleanup after all tests
	 ***************************/
	 err = tcleanup(&sessionid);
	 return testfail;

}

#include <tsetup.c>
