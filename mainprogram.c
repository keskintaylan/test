#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include "asn1crt.h"

#include "oss_auto_tcs.h"

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	int totalErrors = 0;
	flag result;
	int errCode;

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket tmp0;
	        Rocket_Initialize(&tmp0);
	    }
	static Rocket tmp = 
	        {
	            .range = LLONG_MIN,
	            .name = "  ",
	            .message = "",
	            .fuel = solid,
	            .speed = {
	                .kind = mph_PRESENT,
	                .u = { .mph = LLONG_MIN}
	            },
	            .payload = {    .nCount = 0,    .arr = 
	                {
	                    
	                }
	            },
	            .exist = {
	                .speed = 1
	            }
	        };
			
		result = Rocket_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_1 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_1' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_1' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_1' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_1'\n");
			}
			printf("Test Value was rocket_1 Rocket ::= {range -9223372036854775808, name '  ', message '', fuel solid, speed mph:-9223372036854775808, payload {}}\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket tmp0;
	        Rocket_Initialize(&tmp0);
	    }
	static Rocket tmp = 
	        {
	            .range = LLONG_MIN,
	            .name = "  ",
	            .message = "",
	            .fuel = solid,
	            .speed = {
	                .kind = mph_PRESENT,
	                .u = { .mph = 0}
	            },
	            .payload = {    .nCount = 0,    .arr = 
	                {
	                    
	                }
	            },
	            .exist = {
	                .speed = 0
	            }
	        };
			
		result = Rocket_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_2 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_2' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_2' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_2' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_2'\n");
			}
			printf("Test Value was rocket_2 Rocket ::= {range -9223372036854775808, name '  ', message '', fuel solid, payload {}}\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_payload tmp0;
	        Rocket_payload_Initialize(&tmp0);
	    }
	static Rocket_payload tmp = 
	        {    .nCount = 0,    .arr = 
	            {
	                
	            }
	        };
			
		result = Rocket_payload_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_payload_1 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_payload_1' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_payload_1' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_payload_1' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_payload_1'\n");
			}
			printf("Test Value was rocket-payload_1 Rocket-payload ::= {}\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_payload tmp0;
	        Rocket_payload_Initialize(&tmp0);
	    }
	static Rocket_payload tmp = 
	        {    .nCount = 7,    .arr = 
	            {
	                "  ",
	                "  ",
	                "  ",
	                "  ",
	                "  ",
	                "  ",
	                "  "        
	            }
	        };
			
		result = Rocket_payload_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_payload_2 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_payload_2' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_payload_2' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_payload_2' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_payload_2'\n");
			}
			printf("Test Value was rocket-payload_2 Rocket-payload ::= {'  ' '  ' '  ' '  ' '  ' '  ' '  '}\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_payload tmp0;
	        Rocket_payload_Initialize(&tmp0);
	    }
	static Rocket_payload tmp = 
	        {    .nCount = 0,    .arr = 
	            {
	                
	            }
	        };
			
		result = Rocket_payload_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_payload_3 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_payload_3' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_payload_3' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_payload_3' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_payload_3'\n");
			}
			printf("Test Value was rocket-payload_3 Rocket-payload ::= {}\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_payload tmp0;
	        Rocket_payload_Initialize(&tmp0);
	    }
	static Rocket_payload tmp = 
	        {    .nCount = 7,    .arr = 
	            {
	                "             ",
	                "             ",
	                "             ",
	                "             ",
	                "             ",
	                "             ",
	                "             "        
	            }
	        };
			
		result = Rocket_payload_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_payload_4 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_payload_4' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_payload_4' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_payload_4' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_payload_4'\n");
			}
			printf("Test Value was rocket-payload_4 Rocket-payload ::= {'             ' '             ' '             ' '             ' '             ' '             ' '             '}\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_speed tmp0;
	        Rocket_speed_Initialize(&tmp0);
	    }
	static Rocket_speed tmp = 
	        {
	            .kind = mph_PRESENT,
	            .u = { .mph = LLONG_MIN}
	        };
			
		result = Rocket_speed_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_speed_1 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_speed_1' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_speed_1' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_speed_1' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_speed_1'\n");
			}
			printf("Test Value was rocket-speed_1 Rocket-speed ::= mph:-9223372036854775808\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_speed tmp0;
	        Rocket_speed_Initialize(&tmp0);
	    }
	static Rocket_speed tmp = 
	        {
	            .kind = mph_PRESENT,
	            .u = { .mph = 0}
	        };
			
		result = Rocket_speed_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_speed_2 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_speed_2' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_speed_2' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_speed_2' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_speed_2'\n");
			}
			printf("Test Value was rocket-speed_2 Rocket-speed ::= mph:0\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_speed tmp0;
	        Rocket_speed_Initialize(&tmp0);
	    }
	static Rocket_speed tmp = 
	        {
	            .kind = mph_PRESENT,
	            .u = { .mph = 9223372036854775807LL}
	        };
			
		result = Rocket_speed_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_speed_3 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_speed_3' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_speed_3' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_speed_3' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_speed_3'\n");
			}
			printf("Test Value was rocket-speed_3 Rocket-speed ::= mph:9223372036854775807\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_speed tmp0;
	        Rocket_speed_Initialize(&tmp0);
	    }
	static Rocket_speed tmp = 
	        {
	            .kind = kmph_PRESENT,
	            .u = { .kmph = LLONG_MIN}
	        };
			
		result = Rocket_speed_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_speed_4 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_speed_4' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_speed_4' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_speed_4' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_speed_4'\n");
			}
			printf("Test Value was rocket-speed_4 Rocket-speed ::= kmph:-9223372036854775808\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_speed tmp0;
	        Rocket_speed_Initialize(&tmp0);
	    }
	static Rocket_speed tmp = 
	        {
	            .kind = kmph_PRESENT,
	            .u = { .kmph = 0}
	        };
			
		result = Rocket_speed_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_speed_5 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_speed_5' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_speed_5' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_speed_5' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_speed_5'\n");
			}
			printf("Test Value was rocket-speed_5 Rocket-speed ::= kmph:0\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_speed tmp0;
	        Rocket_speed_Initialize(&tmp0);
	    }
	static Rocket_speed tmp = 
	        {
	            .kind = kmph_PRESENT,
	            .u = { .kmph = 9223372036854775807LL}
	        };
			
		result = Rocket_speed_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_speed_6 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_speed_6' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_speed_6' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_speed_6' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_speed_6'\n");
			}
			printf("Test Value was rocket-speed_6 Rocket-speed ::= kmph:9223372036854775807\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	Rocket_fuel tmp0;
	        Rocket_fuel_Initialize(&tmp0);
	    }
	Rocket_fuel tmp = 
	        solid;
			
		result = Rocket_fuel_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_fuel_1 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_fuel_1' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_fuel_1' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_fuel_1' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_fuel_1'\n");
			}
			printf("Test Value was rocket-fuel_1 Rocket-fuel ::= solid\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	Rocket_fuel tmp0;
	        Rocket_fuel_Initialize(&tmp0);
	    }
	Rocket_fuel tmp = 
	        liquid;
			
		result = Rocket_fuel_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_fuel_2 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_fuel_2' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_fuel_2' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_fuel_2' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_fuel_2'\n");
			}
			printf("Test Value was rocket-fuel_2 Rocket-fuel ::= liquid\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	Rocket_fuel tmp0;
	        Rocket_fuel_Initialize(&tmp0);
	    }
	Rocket_fuel tmp = 
	        gas;
			
		result = Rocket_fuel_BER_enc_dec(&tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_fuel_3 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_fuel_3' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_fuel_3' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_fuel_3' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_fuel_3'\n");
			}
			printf("Test Value was rocket-fuel_3 Rocket-fuel ::= gas\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_message tmp0;
	        Rocket_message_Initialize(tmp0);
	    }
	static Rocket_message tmp = 
	        "";
			
		result = Rocket_message_BER_enc_dec(tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_message_1 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_message_1' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_message_1' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_message_1' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_message_1'\n");
			}
			printf("Test Value was rocket-message_1 Rocket-message ::= ''\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_message tmp0;
	        Rocket_message_Initialize(tmp0);
	    }
	static Rocket_message tmp = 
	        "                   ";
			
		result = Rocket_message_BER_enc_dec(tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_message_2 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_message_2' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_message_2' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_message_2' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_message_2'\n");
			}
			printf("Test Value was rocket-message_2 Rocket-message ::= '                   '\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_name tmp0;
	        Rocket_name_Initialize(tmp0);
	    }
	static Rocket_name tmp = 
	        "  ";
			
		result = Rocket_name_BER_enc_dec(tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_name_1 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_name_1' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_name_1' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_name_1' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_name_1'\n");
			}
			printf("Test Value was rocket-name_1 Rocket-name ::= '  '\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_name tmp0;
	        Rocket_name_Initialize(tmp0);
	    }
	static Rocket_name tmp = 
	        "            ";
			
		result = Rocket_name_BER_enc_dec(tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_name_2 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_name_2' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_name_2' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_name_2' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_name_2'\n");
			}
			printf("Test Value was rocket-name_2 Rocket-name ::= '            '\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_payload_elm tmp0;
	        Rocket_payload_elm_Initialize(tmp0);
	    }
	static Rocket_payload_elm tmp = 
	        "  ";
			
		result = Rocket_payload_elm_BER_enc_dec(tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_payload_elm_1 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_payload_elm_1' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_payload_elm_1' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_payload_elm_1' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_payload_elm_1'\n");
			}
			printf("Test Value was rocket-payload-elm_1 Rocket-payload-elm ::= '  '\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

	{
	    {
	        // dummy statement used for calling init functions
	static Rocket_payload_elm tmp0;
	        Rocket_payload_elm_Initialize(tmp0);
	    }
	static Rocket_payload_elm tmp = 
	        "             ";
			
		result = Rocket_payload_elm_BER_enc_dec(tmp, &errCode);
		if (!result) {
			switch(errCode)
			{
			case 1:
				printf("Test case rocket_payload_elm_2 failed in encoding\n");
				break;
			case 2:
				printf("Test case 'rocket_payload_elm_2' failed in decoding\n");
				break;
			case 3:
				printf("Test case 'rocket_payload_elm_2' failed in the validation of the decoded message\n");
				break;
			case 4:
				printf("Test case 'rocket_payload_elm_2' failed. Encoded and decoded messages are different\n");
				break;
			default:
				printf("Unexpected error code in test case 'rocket_payload_elm_2'\n");
			}
			printf("Test Value was rocket-payload-elm_2 Rocket-payload-elm ::= '             '\n");
			printf("========================================\n");
			totalErrors = totalErrors + 1;
		};
	}

    if (totalErrors > 0 ) {
        printf("%d out of 21 failed.", totalErrors); 
        return 1;
    } else {
        printf("All test cases (21) run successfully."); 
        return 0;
    };

}