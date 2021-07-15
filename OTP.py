import smtplib
import sys

gmail_user = 'securingfile.ai@gmail.com'   # Enter your gmail username
gmail_password = ''  # Enter your password

sent_from = gmail_user

to = [sys.argv[1]];
subject = 'OTP Notification'
OTP = sys.argv[2];
body = " OTP for accessing the file from server is: "+OTP+" \n This is system generated mail, Kindly do not reply."

email_text = """\
From: %s
To: %s
Subject: %s

%s
""" % (sent_from, ", ".join(to), subject, body)



server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
server.ehlo()
server.login(gmail_user, gmail_password)
server.sendmail(sent_from, to, email_text)
server.close()

print ('Email sent!')
#except:
#    print ('Something went wrong...')
