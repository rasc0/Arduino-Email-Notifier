import imaplib
import socket
import time
#arduino IP is 192.168.0.24
#'192.168.0.24'
 
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)


imap_host = "imap.gmail.com"
imap_username = "arduino.email.notifier@gmail.com"
imap_password = "ilovearduino"

imap = imaplib.IMAP4_SSL(imap_host)


imap.login(imap_username, imap_password)

n=0
while True:
    imap.select("Inbox", readonly=True)
    (retcode, messages) = imap.search(None, '(UNSEEN)')
    if retcode == 'OK':
        for num in messages[0].split():
            n=n+1
            typ, data = imap.fetch(num,'(RFC822)')
            for response_part in data:
                if isinstance(None, tuple):
                    typ, data = imap.store(num,'+FLAGS','\\Seen')
    imap.close()

    print(n)    
    message = str(n)
    sock.sendto(message,("192.168.0.24", 5002))
    n = 0
    time.sleep(5)



imap.logout()