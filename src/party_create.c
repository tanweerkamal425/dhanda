#include<dhanda/dhanda.h>
#include<dhanda/party.h>

int party_add(dhanda *app, party *party)
{
      struct party p;
      int new_id;
      int ret1, ret2;

      //app->error_str = "Some error occured while adding new party";
      // app_error_set(app, "error format");
      

      debug_print("");

      fseek(app->party_fp, 0, SEEK_END);
      if(!ftell(app->party_fp)) {
           new_id = 1; 
      }else{
           fseek(app->party_fp, -sizeof(*party), SEEK_END);
           ret1 = fread(&p, sizeof(p), 1, app->party_fp);
           if(ret1 != 1) {
               app_error_set(app, strerror(errno));
               return -1; 
           }
          new_id = p.id;
          new_id++; 
     }
      party->id = new_id;

      ret2 = fwrite(party, sizeof(*party), 1, app->party_fp);
      if (ret2 != 1) {
         app_error_set(app, strerror(errno));
         return -1; 
     }

      app_success_set(app, "Party added successfully");
      return 0;
	    
}

