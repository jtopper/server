#include "soap/UAService.nsmap"

#ifdef GSOAP_APACHE
#include "apache_gsoap.h"
IMPLEMENT_GSOAP_SERVER()
#endif

#ifdef GSOAP_STANDALONE
int main(int argc, char **argv)
{ int m, s; /* master and slave sockets */
  struct soap soap;
  soap_init(&soap);
  if (argc < 2)
    soap_serve(&soap);	/* serve as CGI application */
  else
  { m = soap_bind(&soap, NULL, atoi(argv[1]), 100);
    if (m < 0)
    { soap_print_fault(&soap, stderr);
      exit(-1);
    }
    fprintf(stderr, "Socket connection successful: master socket = %d\n", m);
    for ( ; ; )
    { s = soap_accept(&soap);
      fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);
      if (s < 0)
      { soap_print_fault(&soap, stderr);
        exit(-1);
      }
      soap_serve(&soap);
      soap_end(&soap);
    }
  }
  return 0;
}
#endif

int ns__currentTime(struct soap *soap, long& response)
{
   response = time(NULL);
   return SOAP_OK;
}
