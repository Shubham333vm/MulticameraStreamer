#include <gst/gst.h>
#include <pthread.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include <my_global.h>
#include <mysql.h>
#include "CameraRemovedPlayer.h"

#define BUFSIZE 128
#define MAX_CHARS 128
#define N_NO_OF_LINES 10

int value,value1;
char **new_line = NULL;
char **new_line2 = NULL;
//#include <zeitgeist.h>
#define FULL_PATH_SIZE 30


#define STRING_SIZE 50

#define DROP_SAMPLE_TABLE "DROP TABLE IF EXISTS test_table"
#define CREATE_SAMPLE_TABLE "CREATE TABLE Recording_DATA(   ID INT(5) NOT NULL AUTO_INCREMENT,\
                                                            Train_No VARCHAR(40),\
                                                            Coach_No VARCHAR(40),\
                                                            DVR_Id VARCHAR(40),\
                                                            No_Of_Cameras VARCHAR(40), \
                                                            Camera_Name1 VARCHAR(50),\
                                                            Camera_Name2 VARCHAR(50),\
                                                            CameraIP1 VARCHAR(50),\
                                                            CameraIP2 VARCHAR(52),\
                                                            CameraModel VARCHAR(50), \
                                                            Location VARCHAR(50), \
                                                            Date_Of_Installation TIMESTAMP,\
                                                            PRIMARY KEY (ID)       )"
#define INSERT_SAMPLE "INSERT INTO \
                Recording_DATA(Train_No,Coach_No,DVR_Id,No_Of_Cameras,Camera_Name1,Camera_Name2,CameraIP1,CameraIP2,CameraModel,Location) \
                       VALUES(?,?,?,?,?,?,?,?,?,?)"


#define GST_CAT_DEFAULT gst_multi_file_sink_debug

#define DEFAULT_LOCATION "%05d"
#define DEFAULT_INDEX 0
#define DEFAULT_POST_MESSAGES FALSE
#define DEFAULT_NEXT_FILE GST_MULTI_FILE_SINK_NEXT_BUFFER
#define DEFAULT_MAX_FILES 0
#define DEFAULT_MAX_FILE_SIZE G_GUINT64_CONSTANT(2*1024*1024*1024)
#define DEFAULT_MAX_FILE_DURATION GST_CLOCK_TIME_NONE
#define DEFAULT_AGGREGATE_GOPS FALSE


enum
{
  PROP_0,
  PROP_LOCATION,
  PROP_INDEX,
  PROP_POST_MESSAGES,
  PROP_NEXT_FILE,
  PROP_MAX_FILES,
  PROP_MAX_FILE_SIZE,
  PROP_MAX_FILE_DURATION,
  PROP_AGGREGATE_GOPS

};

/* Structure to contain all our information, so we can pass it to callbacks */

typedef struct _CustomData
{
  GstElement *pipeline;
  GstElement *source;
  GstElement *convert;
  GstElement *sink;
  GstElement *videoconvert1, *videoconvert2;
  GstElement *tee;
  GstElement *frameratefilter, *videorate;
  GstElement *queue1, *queue2;
  GstElement *avenc, *avimux;
            
  GstElement *filesink,*filesink2,*filesink3;
  GstPadTemplate *tee_src_pad_template;
  GstPad *teepad1, *teepad2, *qpad1, *qpad2;
  gchar *cset_first;
  gchar *savefile;
  GOptionContext *ctx;
  gchar* gchararray[20];
 
} CustomData;


 /* Handler for the pad-added signal */
  static void pad_added_handler (GstElement *src, GstPad *pad, CustomData *data);
  const gchar *gst_structure_get_string (const GstStructure *structure, const gchar *fieldname);
  int getSubString(char *source, char *target,int from, int to);
  void finish_with_error(MYSQL *con);
   int parse_output();
  void * camera1(void * u);
  void * camera2(void * u);
  void * camera3(void * u);
  void * camera4(void * u);
  void * camera5(void * u);
  void * camera6(void * u);
  void * camera7(void * u);
  void * camera8(void * u);
void parse_output2(char *cmd2);
  pthread_t audio,tid0,tid,tid2,tid3,tid4,tid5,tid6,tid7,tid8;
  int i=0;
int RecursiveCall=0;
  char message[11][70];
  char address[]="/home/shubham/splintng";
  char buffer[0];
  char prop[36];
  static FILE *file_in;
  char message1[41];
  char *ptr;
  gchar *uri;
  const GstStructure *s;
 gboolean terminate = FALSE;
  char fullpath[30];
  const gchar *filename;
  int cameraOneCompleted=0;
  //gint index;
  //GTimeVal *result;
  GstClockTime timestamp, stream_time, running_time, duration;
  guint64 offset, offset_end;
 
  gchar *zeitgeist_timestamp_to_iso8601 (gint64 timestamp);
  void zeitgeist_timestamp_to_timeval (gint64 timestamp,GTimeVal *result);
  char MY_TIME[50];
  char buff3[150]={0,};
    char cmd2[150] = "cd /home/bitcomm-06/Gstreamer/Videos/Cam1/";
    char camera2path[200] = "cd /home/bitcomm-06/Gstreamer/Videos/Cam2/";
    char camera3path[200] = "cd /home/bitcomm-06/Gstreamer/Videos/Cam3/";
    char camera4path[200] = "cd /home/bitcomm-06/Gstreamer/Videos/Cam4/";
    char camera5path[200] = "cd /home/bitcomm-06/Gstreamer/Videos/Cam5/";
    char camera6path[200] = "cd /home/bitcomm-06/Gstreamer/Videos/Cam6/";
    char camera7path[200] = "cd /home/bitcomm-06/Gstreamer/Videos/Cam7/";
    char camera8path[200] = "cd /home/bitcomm-06/Gstreamer/Videos/Cam8/";
   char camera2buffer[200]={0,};
   char camera3buffer[200]={0,};
   char camera4buffer[200]={0,};
   char camera5buffer[200]={0,};
   char camera6buffer[200]={0,};
   char camera7buffer[200]={0,};
   char camera8buffer[200]={0,};

 int main(int argc, char *argv[])

{

         
       // char fullpath[30];
    //    time_t t = time(NULL);
    //struct tm *tt = localtime(&t);
       // sprintf(fullpath, "/home/Videos/Date%02d%02d%d/CAM1",tt->tm_mday,tt->tm_mon + 1, tt-> tm_year + 1900);
      //  sprintf(fullpath, "/home/Videos/Date%02d%02d%d/CAM1",tt->tm_mday,tt->tm_mon + 1, tt-> tm_year + 1900);
    //mkdir(fullpath,0777);
        //time_t t = time(NULL);
    //struct tm *tt = localtime(&t);
 
       /*declare and initialise variable*/
        int i=0;
        file_in=fopen("/home/bitcomm-06/Gstreamer/Id.txt","r");
       /*stores and prints the data from the string*/
     
        while(fgets(buffer,70,file_in)!=NULL)
        {
            strcpy(message[i],buffer);
            i++;
            //nothing  
        }
 
    parse_output();    
  
    strcat(cmd2,new_line[0]);
    strcat(camera2path,new_line[0]);
 strcat(camera3path,new_line[0]);
 strcat(camera4path,new_line[0]);
 strcat(camera5path,new_line[0]);
 strcat(camera6path,new_line[0]);
 strcat(camera7path,new_line[0]);
 strcat(camera8path,new_line[0]);

   // printf("path is =========================================%s",cmd2);
   // printf("path is =========================================%s",cmd2);
   // printf("path is =========================================%s",cmd2);
    strncpy(buff3,cmd2,strlen(cmd2)-1);
    strncpy(camera2buffer,camera2path,strlen(camera2path)-1);
    strncpy(camera3buffer,camera3path,strlen(camera3path)-1);
	strncpy(camera4buffer,camera4path,strlen(camera4path)-1);
	strncpy(camera5buffer,camera5path,strlen(camera5path)-1);
	strncpy(camera6buffer,camera6path,strlen(camera6path)-1);
	strncpy(camera7buffer,camera7path,strlen(camera7path)-1);
	strncpy(camera8buffer,camera8path,strlen(camera8path)-1);
  //  printf("path is =========================================%s",buff3);
  //  printf("path is =========================================%s",buff3);
   // printf("Buffer is =========================================%s",buff3);
   // printf("Buffer is =========================================%s",buff3);
    char newCommand[]=" && ls -t";
    strcat(buff3,newCommand);
   
    strcat(camera2buffer,newCommand);
strcat(camera3buffer,newCommand);
strcat(camera4buffer,newCommand);
strcat(camera5buffer,newCommand);
strcat(camera6buffer,newCommand);
strcat(camera7buffer,newCommand);
strcat(camera8buffer,newCommand);

    ///////////////////Getting Folder Name\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

MYSQL *con =  mysql_init(NULL);
MYSQL_STMT    *stmt;
MYSQL_BIND    bind[10];
my_ulonglong  affected_rows;
int           param_count;

int           int_data;
short         small_data;
char          str_data1[STRING_SIZE],str_data2[STRING_SIZE],str_data3[STRING_SIZE],str_data4[STRING_SIZE],str_data5[STRING_SIZE],
              str_data6[STRING_SIZE],str_data7[STRING_SIZE],str_data8[STRING_SIZE],str_data9[STRING_SIZE],str_data10[STRING_SIZE];

unsigned long str_length1,str_length2,str_length3,str_length4,str_length5,str_length6,str_length7,str_length8,str_length9,str_length10;
my_bool       is_null;

  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "bitcomm",
          "Media", 0, NULL, 0) == NULL)
  {
      //finish_with_error(con);
  }  
 
if (mysql_query(con, DROP_SAMPLE_TABLE))
{
  fprintf(stderr, " DROP TABLE failed\n");
  fprintf(stderr, " %s\n", mysql_error(con));
  exit(0);
}

if (mysql_query(con, CREATE_SAMPLE_TABLE))
{
   fprintf(stderr, " CREATE TABLE failed\n");
   fprintf(stderr, " %s\n", mysql_error(con));
  //exit(0);
}

/* Prepare an INSERT query with 3 parameters */
/* (the TIMESTAMP column is not named; the server */
/*  sets it to the current date and time) */
stmt = mysql_stmt_init(con);
if (!stmt)
{
  fprintf(stderr, " mysql_stmt_init(), out of memory\n");
  exit(0);
}
if (mysql_stmt_prepare(stmt, INSERT_SAMPLE, strlen(INSERT_SAMPLE)))
{
  fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}
fprintf(stdout, " prepare, INSERT successful\n");

/* Get the parameter count from the statement */
param_count= mysql_stmt_param_count(stmt);
fprintf(stdout, " total parameters in INSERT: %d\n", param_count);

if (param_count != 10) /* validate parameter count */
{
  fprintf(stderr, " invalid parameter count returned by MySQL\n");
  exit(0);
}

/* Bind the data for all 3 parameters */

memset(bind, 0, sizeof(bind));

/* INTEGER PARAM */
/* This is a number type, so there is no need
   to specify buffer_length */
//bind[0].buffer_type= MYSQL_TYPE_LONG;
//bind[0].buffer= (char *)&int_data;
//bind[0].is_null= 0;
//bind[0].length= 0;

/* STRING PARAM */
bind[0].buffer_type= MYSQL_TYPE_STRING;
bind[0].buffer= (char *)str_data1;
bind[0].buffer_length= STRING_SIZE;
bind[0].is_null= 0;
bind[0].length= &str_length1;

/* STRING PARAM */
bind[1].buffer_type= MYSQL_TYPE_STRING;
bind[1].buffer= (char *)str_data2;
bind[1].buffer_length= STRING_SIZE;
bind[1].is_null= 0;
bind[1].length= &str_length2;

/* STRING PARAM */
bind[2].buffer_type= MYSQL_TYPE_STRING;
bind[2].buffer= (char *)str_data3;
bind[2].buffer_length= STRING_SIZE;
bind[2].is_null= 0;
bind[2].length= &str_length3;

/* STRING PARAM */
bind[3].buffer_type= MYSQL_TYPE_STRING;
bind[3].buffer= (char *)str_data4;
bind[3].buffer_length= STRING_SIZE;
bind[3].is_null= 0;
bind[3].length= &str_length4;

/* STRING PARAM */
bind[4].buffer_type= MYSQL_TYPE_STRING;
bind[4].buffer= (char *)str_data5;
bind[4].buffer_length= STRING_SIZE;
bind[4].is_null= 0;
bind[4].length= &str_length5;

/* STRING PARAM */
bind[5].buffer_type= MYSQL_TYPE_STRING;
bind[5].buffer= (char *)str_data6;
bind[5].buffer_length= STRING_SIZE;
bind[5].is_null= 0;
bind[5].length= &str_length6;

/* STRING PARAM */
bind[6].buffer_type= MYSQL_TYPE_STRING;
bind[6].buffer= (char *)str_data7;
bind[6].buffer_length= STRING_SIZE;
bind[6].is_null= 0;
bind[6].length= &str_length7;

/* STRING PARAM */
bind[7].buffer_type= MYSQL_TYPE_STRING;
bind[7].buffer= (char *)str_data8;
bind[7].buffer_length= STRING_SIZE;
bind[7].is_null= 0;
bind[7].length= &str_length8;

/* STRING PARAM */
bind[8].buffer_type= MYSQL_TYPE_STRING;
bind[8].buffer= (char *)str_data9;
bind[8].buffer_length= STRING_SIZE;
bind[8].is_null= 0;
bind[8].length= &str_length9;

bind[9].buffer_type= MYSQL_TYPE_STRING;
bind[9].buffer= (char *)str_data10;
bind[9].buffer_length= STRING_SIZE;
bind[9].is_null= 0;
bind[9].length= &str_length10;

/* SMALLINT PARAM */
//bind[2].buffer_type= MYSQL_TYPE_SHORT;
//bind[2].buffer= (char *)&small_data;
//bind[2].is_null= &is_null;
//bind[2].length= 0;

/* Bind the buffers */
if (mysql_stmt_bind_param(stmt, bind))
{
  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}

/* Specify the data values for the first row */
//int_data= 10;             /* integer */
strncpy(str_data1, message[0]+9, STRING_SIZE);
str_length1= strlen(str_data1);
strncpy(str_data2, message[1]+9, STRING_SIZE);
str_length2= strlen(str_data2);
strncpy(str_data3, message[2]+7, STRING_SIZE);
str_length3= strlen(str_data3);
strncpy(str_data4, message[3]+14, STRING_SIZE);
str_length4= strlen(str_data4);
strncpy(str_data5, message[4]+13, STRING_SIZE);
str_length5= strlen(str_data5);
strncpy(str_data6, message[5]+13, STRING_SIZE);
str_length6= strlen(str_data6);
strncpy(str_data7, message[6]+10, STRING_SIZE);
str_length7= strlen(str_data7);
strncpy(str_data8, message[7]+10, STRING_SIZE);
str_length8= strlen(str_data8);
strncpy(str_data9, message[8]+12, STRING_SIZE);
str_length9= strlen(str_data9);
strncpy(str_data10, message[9]+9, STRING_SIZE);
str_length10= strlen(str_data10); /* string  */

printf("first%s\n",message[0]+9);
printf("second%s\n",message[1]+9);
printf("third%s\n",message[2]+7);
printf("fourth%s\n",message[3]+14);
printf("fifith%s\n",message[4]+13);
printf("sixth%s\n",message[5]+13);
printf("seventh%s\n",message[6]+11);
printf("eight%s\n",message[8]+11);
printf("nine%s\n",message[8]);
printf("tenth%s\n",message[9]);
printf("tenth%s\n",message[7]);

/* INSERT SMALLINT data as NULL */
is_null= 1;

/* Execute the INSERT statement - 1*/

if (mysql_stmt_execute(stmt))
{
  fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}

/* Get the number of affected rows */
affected_rows= mysql_stmt_affected_rows(stmt);
fprintf(stdout, " total affected rows(insert 1): %lu\n",
                (unsigned long) affected_rows);

if (affected_rows != 1) /* validate affected rows */
{
  fprintf(stderr, " invalid affected rows by MySQL\n");
  exit(0);
}



/* Close the statement */
if (mysql_stmt_close(stmt))
{
  /* mysql_stmt_close() invalidates stmt, so call          */
  /* mysql_error(mysql) rather than mysql_stmt_error(stmt) */
  fprintf(stderr, " failed while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_error(con));
  exit(0);
}

  //mysql_close(con);
 // exit(0);

      // prop[37]='\n';

   // printf("%u\n",message[6]);

   //printf("dfsgvdfvbfdvb%s\n",prop);
  // printf("dfsgvdfvbfdvb%s\n",message[6]);


/* Initialize GStreamer */
   gst_init (&argc, &argv);
   int err,err1;

 
 //while(1)
//{

  
  char fileName[]="Sweet";

  pthread_create(&audio,NULL,&BackgroundMusic,fileName);
  pthread_create(&tid,NULL,&camera1,NULL);
  printf("Main thread is waiting for audio to complete");
//  pthread_create(&tid2,NULL,&camera2,NULL);
//  pthread_create(&tid3,NULL,&camera3,NULL);
//  pthread_create(&tid4,NULL,&camera4,NULL);
//  pthread_create(&tid5,NULL,&camera5,NULL);
//  pthread_create(&tid6,NULL,&camera6,NULL);
//  pthread_create(&tid7,NULL,&camera7,NULL);
//  pthread_create(&tid8,NULL,&camera8,NULL);
  // sleep(1009);
  //pthread_cancel(tid);
//printf("main sleeping\n");
//sleep(500000);
//}
 

 pthread_join(tid,NULL);
//while(cameraOneCompleted!=0)
//{

//camera1(NULL);
 //cameraOneCompleted=0;
//printf("Value of terminate========================================= %d\n",terminate);
 //pthread_create(&tid0,NULL,&camera1,NULL);
//pthread_join(tid0,NULL);
//printf("22222222222222222222222222222222222222222222222222222222222222");
 
//printf("33333333333333333333333333333333333333333333333333333333333333");
//}

printf("Camera one is completed its time");
//pthread_join(audio,NULL);

 
 
  //pthread_join(tid2,NULL);
 // pthread_join(tid3,NULL);
 // pthread_join(tid4,NULL); 
 // pthread_join(tid5,NULL);
 //pthread_join(tid6,NULL); 
 //pthread_join(tid7,NULL);
  //pthread_join(tid8,NULL);
   return 0;
 
//return EXIT_SUCCESS;
}


 
  BackgroundMusic(char *p);



     void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);      
}
 
///////////////////////////////////////////////////Date Folder \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    int parse_output() {
    char *cmd = "cd /home/bitcomm-06/Gstreamer/Videos/Cam1 && ls -t";    
    char line[MAX_CHARS] = {0};
    
    int noOfLines = 0;
    int lineCount = 0;

    char buf[BUFSIZE];
    FILE *fp;
    int i;
    new_line = malloc(sizeof(char*) * N_NO_OF_LINES);
    noOfLines = N_NO_OF_LINES;
    if ((fp = popen(cmd,"r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }
    while (fgets(buf, BUFSIZE, fp) != NULL) {
        // Do whatever you want here...
        //strcpy(arr[i],buf); 
        if (lineCount >= noOfLines)
        {
            new_line = realloc(new_line, (sizeof(char*)*(noOfLines+N_NO_OF_LINES)));
            noOfLines += N_NO_OF_LINES;
        }
        new_line[lineCount] = strdup(buf);
       // printf("OUTPUT: %s", buf);
        lineCount++;
        //printf("OUTPUT: %s\n%s", buf,new_line[lineCount]);
    }

    if(pclose(fp))  {
        printf("Command not found or exited with error status\n");
        return -1;
    }
    for (i = 0; i < lineCount; ++i)
    {
        /* code */
      //  printf("Value through indexing %s", new_line[i]);
       // printf("Value through dereferencing%s", *new_line);
    }
    
    
    return 0;
}



/////////////////////////////////////Rename\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


void parse_output2(char *cmd2) {


    //char cmd4[200] ={};
 // strncpy(cmd4,*cmd,)
     //sprintf(cmd4,"%s",cmd2);
//printf("parse_output2 %s", cmd4);
  //  while(1)
   // {   
   // printf("cmd2 value=======%s\n",cmd2);
    //char *cmd = cmd2;   
    char line[MAX_CHARS] = {0};
   
    int noOfLines = 0;
    int lineCount = 0;

    char buf[BUFSIZE];
    FILE *fp;
    int i;
    new_line2 = malloc(sizeof(char*) * N_NO_OF_LINES);
    noOfLines = N_NO_OF_LINES;
    if ((fp = popen(cmd2, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return ;
    }
    while (fgets(buf, BUFSIZE, fp) != NULL) {
        // Do whatever you want here...
        //strcpy(arr[i],buf);
        if (lineCount >= noOfLines)
        {
            new_line2 = realloc(new_line2, (sizeof(char*)*(noOfLines+N_NO_OF_LINES)));
            noOfLines += N_NO_OF_LINES;
        }
        new_line2[lineCount] = strdup(buf);
       // printf("OUTPUT: %s", buf);
        lineCount++;
        //printf("OUTPUT: %s\n%s", buf,new_line[lineCount]);
    }

    if(pclose(fp))  {
       // printf("Command not found or exited with error status\n");
        return ;
    }
    for (i = 0; i < lineCount; ++i)
    {
      /* code */
       // printf("Value through indexing %s\n", new_line[i]);
        // printf("Size of ============================array==== %d",lineCount);
        //  printf("CMD ============================array==== %s",cmd2);
        // printf("Value through dereferencing%s", *new_line);
    }
  time_t t ;
     struct tm *tmp ;
  
     time( &t );

     tmp = localtime( &t );
     char str[20]={0,};
    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%c", tmp);

   char  renamearry[150]={0,};
   char removefilepath[150]={0,};
   char finalPath[150]={0,};
   strncpy(removefilepath,cmd2,strlen(cmd2)-9);
   memcpy(removefilepath,removefilepath+3,sizeof(removefilepath));  
   strcat(removefilepath,"/");
   printf("removefilepath path%s",removefilepath);
   strncpy(renamearry,removefilepath,strlen(removefilepath)-1);
   printf("rename is the final path%s",renamearry);
   printf("strenamercat is the final path%s",renamearry);
   strcat(renamearry,"/");
   char date[100]={0,};
   sprintf(date,"%s",MY_TIME);
   strcat(date,".mp4");
   char path2[2000]={0,};
       strcat(path2,renamearry);
          strcat(path2,date);
    // strcat(renamearry,"/Shubham");
   //  printf("removefilepath path%s",removefilepath);
    strcat(removefilepath,new_line2[0]);
   
    printf("strcat is the final path%s",removefilepath);
   // printf("Length of removefilepath is %d\n",strlen(removefilepath));
    strncpy(finalPath,removefilepath,strlen(removefilepath)-1);
    //printf("Length After removal of finalPath is %d\n",strlen(finalPath));
   // printf("Final removable file path====================================111111%s\n",finalPath);
   //  printf("Final removable file path====================================111111%s",finalPath);
    // printf("This is the final path");
  // rename(removefilepath,renamearry);

   int value;
 

   //  printf("Final removable file path====================================111111%s\n",finalPath);
     //printf("Final removable file path====================================111111%s",path2);

    // File name is changed here
char *c=new_line2[0];

if(c[0]=='R')
{
   value = rename(finalPath, path2);
 
    // Print the result
    if(!value)
    {
        printf("%s\n", "File name changed successfully");
    }
    else
    {
        perror("Error");
    }

}

//free(new_line);
}



/////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  void * camera1(void * u)

  {
 printf("Array data is s==============================================%s",new_line[0]);
      cameraOneCompleted=0;

      printf("Thread starting1....\n");
       
       GstMessage *msg;
      printf("Thread starting2....\n");
     
        CustomData data;
 printf("Thread starting3....\n");
     
        guint bus_watch_id;
 printf("Thread starting4....\n");
     
        GstBus *bus;
 printf("Thread starting5....\n");
     
        GstStateChangeReturn ret;
 printf("Thread starting6....\n");
     
        gboolean terminate = FALSE;
 printf("Thread starting7....\n");
     
        char cam2[9]="cam2";
 printf("Thread starting8....\n");
     
        char num[256];
 printf("Thread starting9....\n");
     
       
        data.source = gst_element_factory_make ("uridecodebin", "source");
printf("Thread starting10....\n");
        data.convert = gst_element_factory_make ("videoconvert", "convert");
printf("Thread starting11....\n");
        data.sink = gst_element_factory_make ("autovideosink", "sink");
printf("Thread starting12....\n");
        data.videoconvert1 = gst_element_factory_make("videoconvert", "videoconvert1");
printf("Thread starting13....\n");
    data.videoconvert2 = gst_element_factory_make("videoconvert", "videoconvert2");
printf("Thread starting14....\n");
    data.queue1 = gst_element_factory_make("queue", "queue1");
printf("Thread starting15....\n");
    data.queue2 = gst_element_factory_make("queue", "queue2");
printf("Thread starting16....\n");
    data.tee = gst_element_factory_make("tee", "tee");
printf("Thread starting17....\n");
  
    data.frameratefilter = gst_element_factory_make("capsfilter", NULL);
printf("Thread starting18...\n");
    data.videorate = gst_element_factory_make("videorate", NULL);
printf("Thread starting19....\n");
    data.avenc = gst_element_factory_make("avenc_mpeg2video", NULL);
printf("Thread starting20....\n");
    data.avimux = gst_element_factory_make("avimux", NULL);
printf("Thread starting21....\n");
    data.filesink = gst_element_factory_make("multifilesink", "filesink");
printf("Thread starting22....\n");
  
     /* Create the empty pipeline */
       data.pipeline = gst_pipeline_new ("test-pipeline");
printf("Thread starting23....\n");
  if (!data.pipeline || !data.source || !data.convert || !data.videoconvert1 || !data.videoconvert2 || !data.queue1 || !data.queue2 || !data.tee || !data.sink || !data.filesink  ) {
    g_printerr ("Not all elements could be created.\n");
    return 0;
  }
printf("Thread starting24....\n");
     //    g_object_set(G_OBJECT (data.filesink), "name", ctime(&t),"async",0, NULL);
        g_object_set(G_OBJECT(data.frameratefilter), "caps", gst_caps_from_string("video/x-raw,framerate=50/1"), NULL);
      printf("Thread starting25....\n");

  /* Build the pipeline. Note that we are NOT linking the source at this
   * point. We will do it later. */
  gst_bin_add_many (GST_BIN (data.pipeline), data.source, data.convert , data.videoconvert1, data.videoconvert2, data.queue1, data.queue2, data.tee, data.sink, data.frameratefilter, data.videorate, data.avenc, data.avimux, data.filesink,NULL);
printf("Thread starting26....\n");
  if (!gst_element_link (data.convert, data.tee)) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
printf("Thread starting27....\n");
if (!gst_element_link_many(data.queue1, data.videoconvert1, data.sink, NULL))
        g_error("Failed to link display elements!");
printf("Thread starting28....\n");
    if (!gst_element_link_many(data.queue2, data.videorate, data.frameratefilter, data.videoconvert2, data.avenc,data.avimux, data.filesink, NULL))

        g_error("Failed to link save elements!");

    if ( !(data.tee_src_pad_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (data.tee), "src_%u"))) {
      g_critical ("Unable to get pad template!");
      return 0;
     }
printf("Thread starting29....\n");
    data.qpad1 = gst_element_get_static_pad(data.queue1, "sink");
printf("Thread starting30....\n");
    data.qpad2 = gst_element_get_static_pad(data.queue2, "sink");
printf("Thread starting31....\n");
    data.teepad1 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
printf("Thread starting32....\n");
    g_print ("Obtained request pad %s for queue1 branch.\n", gst_pad_get_name (data.teepad1));
printf("Thread starting33....\n");
    data.teepad2 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
printf("Thread starting34....\n");
    g_print ("Obtained request pad %s for queue2 branch.\n", gst_pad_get_name (data.teepad2));
printf("Thread starting35....\n");

    if(!data.teepad1 || !data.teepad2 || !data.qpad1 || !data.qpad2){
        g_error("Creation of one tee pad failed.");
        return 0;
    }
printf("Thread starting36....\n");
    gst_pad_link (data.teepad1, data.qpad1);
printf("Thread starting37....\n");
    gst_pad_link (data.teepad2, data.qpad2);
printf("Thread starting38....\n");
    gst_object_unref (GST_OBJECT (data.qpad1));
printf("Thread starting39....\n");
    gst_object_unref (GST_OBJECT (data.qpad2));
printf("Thread starting40....\n");
    gst_object_unref (GST_OBJECT (data.teepad1));
printf("Thread starting41....\n");
    gst_object_unref (GST_OBJECT (data.teepad2));
printf("Thread starting42....\n");
       //uri = gst_filename_to_uri (message[6], NULL);
      

    // Output a dot file of the pipeline
    // Be sure to $ export GST_DEBUG_DUMP_DOT_DIR=/tmp
    // and run with the --gst-enable-gst-debug command line switch
    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(data.pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline_graph");
 printf("Thread starting43....\n");
   printf("%s",message[6]+10);
   printf("%s",message[7]+10);

  /* Set the URI to play */
  g_object_set (data.source, "uri",message[6]+10, NULL);
printf("Thread starting44....\n");
  /* Connect to the pad-added signal */
  g_signal_connect (data.source, "pad-added", G_CALLBACK (pad_added_handler), &data);
printf("Thread starting45....\n");
  //printf("%s",*prop);
  /* Start playing */
  printf("start playing..\n");
 printf("playing..\n");
printf("playing..\n");
printf("playing..\n");
printf("playing..\n");
printf("playing..\n");
printf("playing..\n");
printf("playing..\n");
printf("playing..\n");

if(gst_element_set_state (data.pipeline, GST_STATE_PLAYING))
{
RecursiveCall++;
printf("Recursive call counter=%d",RecursiveCall);
printf("start one playing..\n");
 ret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
}

  else
{
gst_element_set_state (data.pipeline, GST_STATE_NULL);
printf("start two playing..\n");
}
printf("start iss playing..\n");
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
  printf("Thread starting46....\n");
printf("start playing..\n");
printf("start playing..\n");
printf("start playing..\n");
printf("start playing..\n");
printf("start playing..\n");
     char buff[150]; 
printf("Thread starting47....\n");
     char path[150]="//home//bitcomm-06//Gstreamer//Videos//Cam1//";  
printf("Thread starting 48...\n");
printf("Array data is s==============================================%s",new_line[0]);
   //  char path2[]="/home/bitcomm-31/Videos/";  
     strcat(path,new_line[0]);
printf("Thread starting49....\n");
     //strcat(path2,new_line[0]);
     printf("path1 data is s==============================================%s",path);
printf("Thread starting50....\n");
     //printf("path2 data is s==============================================%s",path2);          
   //  printf("Array data is s==============================================%s",new_line[0]);
     char *CurrentDate=new_line[0];
   //  printf("Array data is s==============================================%s",new_line[1]);
     strncpy(buff, path, strlen(path)-1);
     strcat(buff,"//ReplacedByDate_Time%03d.mp4");
     printf("path==============================================%s\n",buff);
     
    // g_object_set(G_OBJECT (data.filesink),"location","fullpath/Cam1_%03d.mp4","async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"location",buff,"async",0, NULL);
    //g_object_set(G_OBJECT (data.filesink),"location",fullpath,"async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"post-messages", TRUE, "async", 0, NULL);   
    g_object_set(G_OBJECT (data.filesink),"next-file", 4,"async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-file-size", 1000000, "async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-files",5, "async", 0, NULL);


printf("Thread Start.. Listen to bus\n");

 /* Listen to the bus */
  bus = gst_element_get_bus (data.pipeline);
printf("Bus status fetched\n");
  do {
 
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
    GST_MESSAGE_ANY);
    //msg=GST_MESSAGE_EOS;
   //printf("Enetring switch case=================================================================\n");
    /* Parse message */
    if (msg != NULL) {
      GError *err;
      gchar *debug_info;
      
      switch (GST_MESSAGE_TYPE (msg)) {

//printf("msg.type------------------------------------------------------------------------------- %s\n",GST_MESSAGE_TYPE (msg));
        case GST_MESSAGE_ERROR:
         // parse_output2(*cmd2);
          gst_message_parse_error (msg, &err, &debug_info);
          g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
          g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
          g_clear_error (&err);
          g_free (debug_info);
          parse_output2(buff3);
          //free(new_line2);
           char fileName[]="OneNetwork";
          CameraRemovedAudioPlayer(fileName);
          sleep(5);
          printf("Cameraone value in side Gst_Message_Error======================%d",cameraOneCompleted);
         // continue;
            printf("Cmd value is ===%s",buff3);
          
          terminate = TRUE;
          cameraOneCompleted=1;


          break;
        case GST_MESSAGE_EOS:
         // 
 //continue;
    cameraOneCompleted=1;
//parse_output2(buff3);
printf("Cmd value is ===%s",buff3);
          g_print ("End-Of-Stream reached.\n");
   //camera1(NULL);
char file[]="OneNetwork";
          CameraRemovedAudioPlayer(file);
          terminate = TRUE;
          break;
        case GST_MESSAGE_STATE_CHANGED:
          /* We are only interested in state-changed messages from the pipeline */
          if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
            g_print ("Pipeline state changed from %s to %s:\n",
                gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
          }
          break;
          //////START
         
       case GST_MESSAGE_UNKNOWN:
        g_print("GST_MESSAGE_UNKNOWN\n");
          break;

    case GST_MESSAGE_ANY:
      //  g_print("GST_MESSAGE_ANY==================GST_MESSAGE_ANY=================GST_MESSAGE_ANY=============GST_MESSAGE_ANY\n");
          break;



case GST_MESSAGE_ELEMENT:
       
     
        s = gst_message_get_structure (msg);
   if (gst_structure_has_name(s, "GstMultiFileSink"))
    {
   
    
     time_t t ;
     struct tm *tmp ;
  
     time( &t );

     tmp = localtime( &t );
     char str[20]={0,};
    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%c", tmp);
    //sprintf(str,%c,MY_TIME);
    printf("date and time-------------------------------------------------------------------------------------------%s\n", MY_TIME );
   
    int i=0, len, j;
	
	len=strlen(MY_TIME);
	for(i=0; i<len; i++)
	{
		if(MY_TIME[i]==' '|| MY_TIME[i]==':')
		{
			MY_TIME[i]='_';
		}
	}
   
         g_print("########################GST_MESSAGE_ELEMENT START CAM 1#################\n");
         g_print("File written.\n");
// printf("CurrentDate is ==============================================%s",CurrentDate);
         filename = gst_structure_get_string (s, "filename");
        // g_print ("filename------------ %s\n",filename);
          char path[1000]={0,};
          char buff1[150]={0,};
          sprintf(path,"%s",filename);
          printf("path---########----------%s\n",path);
         //  g_print ("name-after strcpy--path--------- %s\n",path);
          printf("array data is ==============================================%s",new_line[0]);
          char path3[100]="/home/bitcomm-06/Gstreamer/Videos/Cam1/";
          
         // printf("array data is ==============================================%s",new_line[0]);
          strcat(path3,CurrentDate);
          strncpy(buff1,path3,strlen(path3)-1);
          printf("path3==============================================%s",path3);
          printf("New path==============================================%s",buff1);
          strcat(buff1,"/");
          
         // printf("After strcat path becomes====================================%s",buff1);
          char date[100]={0,};
         
          sprintf(date,"%s",MY_TIME);
          //g_print ("Datrshdgvjksfhnjkgvbjsfbgvkjbf--------- %s\n",date);
          strcat(date,".mp4");
         // g_print ("name-after strcpy--path3 date and time--------- %s\n",date);
          char path2[2000]={0,};
        //  strcat(path,filename);
          strcat(path2,buff1);
          strcat(path2,date);
         // free(new_line);
        printf("Saving fine name is  path is ====================================%s",path2);
       
    int value;
 
    // File name is changed here
   value = rename(path, path2);
 
    // Print the result
    if(!value)
    {
        printf("%s\n", "File name changed successfully");
    }
    else
    {
        perror("Error");
    }
 
         g_print("########################GST_MESSAGE_ELEMENT END CAM 1#################\n");
    }
    break;
         //////END
        default:
        
          break;
      }

      gst_message_unref (msg);
    }
     

        printf("value of terminate--------------------------------------------------------- %d\n",terminate);
  
  } while (!terminate);

//
 // gst_element_release_request_pad (data.queue1, data.qpad1);
  //gst_element_release_request_pad (data.queue2, data.qpad2);
 // gst_object_unref (data.qpad1);
  //gst_object_unref (data.qpad2);
  //gst_caps_unref (new_pad_caps);
  //gst_object_unref (sink_pad);
 //
  //gst_object_unref (bus);
  gst_element_set_state (data.pipeline, GST_STATE_NULL);
  gst_object_unref (data.pipeline);
 gst_message_unref (msg);
  gst_object_unref (data.avenc);
//gst_object_unref (data.sink);
//gst_object_unref (data.source);

printf("Cameraone value outside side Gst_Message_Error======================%d",cameraOneCompleted);

//free(new_line);
 //camera1(NULL);

return 0;
}

  void * camera2(void * u)

  {

    //char fileLocPattern = "/home/shubham/splintng/Videos";
   // char buffer[32];
   // memset(buffer, 0, sizeof(buffer));
   // sprintf(buffer, fileLocPattern.c_str(), i++);
    printf("Thread starting....\n");
       // printf("%s",prop);
       //time_t t;
     //   srand((unsigned) time(&t));
        GstMessage *msg;
     
      //  time(&t);
        CustomData data;
        guint bus_watch_id;
        GstBus *bus;
        GstStateChangeReturn ret;
       
        char cam2[9]="cam2";
        char num[256];
       // data.gchararray="Videos";
       // printf("%s",prop);
      
         /* Create the elements */
    //int oldstate,oldtype;
         //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
        data.source = gst_element_factory_make ("uridecodebin", "source");
        data.convert = gst_element_factory_make ("videoconvert", "convert");
        data.sink = gst_element_factory_make ("autovideosink", "sink");
        data.videoconvert1 = gst_element_factory_make("videoconvert", "videoconvert1");
    data.videoconvert2 = gst_element_factory_make("videoconvert", "videoconvert2");
    data.queue1 = gst_element_factory_make("queue", "queue1");
    data.queue2 = gst_element_factory_make("queue", "queue2");
    data.tee = gst_element_factory_make("tee", "tee");
  
    data.frameratefilter = gst_element_factory_make("capsfilter", NULL);
    data.videorate = gst_element_factory_make("videorate", NULL);
    data.avenc = gst_element_factory_make("avenc_mpeg2video", NULL);
    data.avimux = gst_element_factory_make("avimux", NULL);
    data.filesink = gst_element_factory_make("multifilesink", "filesink");
   // data.splitmuxsink = gst_element_factory_make("splitmuxsink", "splitmuxsink");
      //  data.getchararray = gst_element_factory_make("/home/shubham/splintng/Videos", "getchararray");

       // data.filesink2 = gst_element_factory_make("filesink2", NULL);
  

     /* Create the empty pipeline */
       data.pipeline = gst_pipeline_new ("test-pipeline");

  if (!data.pipeline || !data.source || !data.convert || !data.videoconvert1 || !data.videoconvert2 || !data.queue1 || !data.queue2 || !data.tee || !data.sink || !data.filesink  ) {
    g_printerr ("Not all elements could be created.\n");
    return 0;
  }
     //    g_object_set(G_OBJECT (data.filesink), "name", ctime(&t),"async",0, NULL);
        g_object_set(G_OBJECT(data.frameratefilter), "caps", gst_caps_from_string("video/x-raw,framerate=50/1"), NULL);
       //
  
     
       // g_object_set(G_OBJECT(data.filesink2), "location", strcat(cam22,ctime(&t)), "async", 0, NULL);
  
       // g_object_set(data.avenc, "bitrate", 4096, NULL);

  /* Build the pipeline. Note that we are NOT linking the source at this
   * point. We will do it later. */
  gst_bin_add_many (GST_BIN (data.pipeline), data.source, data.convert , data.videoconvert1, data.videoconvert2, data.queue1, data.queue2, data.tee, data.sink, data.frameratefilter, data.videorate, data.avenc, data.avimux, data.filesink,data.filesink2,NULL);
  if (!gst_element_link (data.convert, data.tee)) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
if (!gst_element_link_many(data.queue1, data.videoconvert1, data.sink, NULL))
        g_error("Failed to link display elements!");
    if (!gst_element_link_many(data.queue2, data.videorate, data.frameratefilter, data.videoconvert2, data.avenc,data.avimux, data.filesink, NULL))
        g_error("Failed to link save elements!");

    if ( !(data.tee_src_pad_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (data.tee), "src_%u"))) {
      g_critical ("Unable to get pad template!");
      return 0;
     }

        data.qpad1 = gst_element_get_static_pad(data.queue1, "sink");
    data.qpad2 = gst_element_get_static_pad(data.queue2, "sink");
    data.teepad1 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue1 branch.\n", gst_pad_get_name (data.teepad1));
    data.teepad2 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue2 branch.\n", gst_pad_get_name (data.teepad2));

    if(!data.teepad1 || !data.teepad2 || !data.qpad1 || !data.qpad2){
        g_error("Creation of one tee pad failed.");
        return 0;
    }

    gst_pad_link (data.teepad1, data.qpad1);
    gst_pad_link (data.teepad2, data.qpad2);

    gst_object_unref (GST_OBJECT (data.qpad1));
    gst_object_unref (GST_OBJECT (data.qpad2));
    gst_object_unref (GST_OBJECT (data.teepad1));
    gst_object_unref (GST_OBJECT (data.teepad2));

       //uri = gst_filename_to_uri (message[6], NULL);
      

    // Output a dot file of the pipeline
    // Be sure to $ export GST_DEBUG_DUMP_DOT_DIR=/tmp
    // and run with the --gst-enable-gst-debug command line switch
    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(data.pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline_graph");
 
   printf("%s",message[6]+10);
   printf("%s",message[7]+10);

  /* Set the URI to play */
  g_object_set (data.source, "uri",message[7]+10, NULL);

  /* Connect to the pad-added signal */
  g_signal_connect (data.source, "pad-added", G_CALLBACK (pad_added_handler), &data);
  //printf("%s",*prop);
  /* Start playing */
  printf("start playing..\n");
  ret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
  
     char buff[150]; 
     char path[150]="//home//bitcomm-06//Gstreamer//Videos//Cam2//";  
   //  char path2[]="/home/bitcomm-31/Videos/";  
     strcat(path,new_line[0]);
     //strcat(path2,new_line[0]);
     printf("path1 data is s==============================================%s",path);
     //printf("path2 data is s==============================================%s",path2);          
     printf("Array data is s==============================================%s",new_line[0]);
     printf("Array data is s==============================================%s",new_line[1]);
     strncpy(buff, path, strlen(path)-1);
     strcat(buff,"//ReplacedByDate_Time%03d.mp4");
     printf("path==============================================%s\n",buff);
     
    // g_object_set(G_OBJECT (data.filesink),"location","fullpath/Cam1_%03d.mp4","async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"location",buff,"async",0, NULL);
    //g_object_set(G_OBJECT (data.filesink),"location",fullpath,"async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"post-messages", TRUE, "async", 0, NULL);   
    g_object_set(G_OBJECT (data.filesink),"next-file", 4,"async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-file-size", 1000000, "async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-files",5, "async", 0, NULL);


printf("Thread Start.. Listen to bus\n");

 /* Listen to the bus */
  bus = gst_element_get_bus (data.pipeline);
printf("Bus status fetched\n");
  do {
 
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
    GST_MESSAGE_ANY);
    //msg=GST_MESSAGE_EOS;
   printf("Enetring switch case\n");
    /* Parse message */
    if (msg != NULL) {
      GError *err;
      gchar *debug_info;
      printf("msg.type %u\n",GST_MESSAGE_TYPE (msg));
      switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_ERROR:
          gst_message_parse_error (msg, &err, &debug_info);
          g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
          g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
          g_clear_error (&err);
          g_free (debug_info);
          terminate = TRUE;

char fileName[]="CameraTwo";
CameraRemovedAudioPlayer(fileName);
parse_output2(camera2buffer);


          break;

        case GST_MESSAGE_EOS:
//parse_output2(buff3);
          g_print ("End-Of-Stream reached.\n");
          terminate = TRUE;
          
          break;
        case GST_MESSAGE_STATE_CHANGED:
          /* We are only interested in state-changed messages from the pipeline */
          if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
            g_print ("Pipeline state changed from %s to %s:\n",
                gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
          }
          break;
          //////START
          case GST_MESSAGE_UNKNOWN:
        g_print("GST_MESSAGE_UNKNOWN\n");
break;
//case GST_MESSAGE_ELEMENT:
//g_print("########################GST_MESSAGE_ELEMENT     START #################\n");
//g_message ("get message %s", gst_structure_get_name (gst_message_get_structure(msg)));
//g_print ("filenemae %d",gst_message_get_structure(msg))->index);
//g_print("########################GST_MESSAGE_ELEMENT     END  #################\n");
//break;

case GST_MESSAGE_ELEMENT:
       
     
        s = gst_message_get_structure (msg);
   if (gst_structure_has_name(s, "GstMultiFileSink"))
    {
   
         //time_t t = time(NULL);
        // struct tm *tm = localtime(&t);
        // printf("%s\n", asctime(tm));
    //==================================================date time spaceless====================\\
  
   
    
    //localtime() uses the time pointed by t ,
    // to fill a tm structure with the
    // values that represent the
    // corresponding local time.
    
     time_t t ;
     struct tm *tmp ;
  
     time( &t );

     tmp = localtime( &t );
     char str[20]={0,};
    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%c", tmp);
    //sprintf(str,%c,MY_TIME);
    printf("date and time---------------%s\n", MY_TIME );
   
    int i=0, len, j;
	
	len=strlen(MY_TIME);
	for(i=0; i<len; i++)
	{
		if(MY_TIME[i]==' '|| MY_TIME[i]==':')
		{
			MY_TIME[i]='_';
		}
	}
    
  
   
     //==================================================date time spaceless====================\\
   
   
         g_print("########################GST_MESSAGE_ELEMENT START CAM 2#################\n");
         g_print("File written.\n");
         filename = gst_structure_get_string (s, "filename");
        // g_print ("filename------------ %s\n",filename);
          char path[1000]={0,};
          char buff1[150]={0,};
          sprintf(path,"%s",filename);
          printf("path---########----------%s\n",path);
           g_print ("name-after strcpy--path--------- %s\n",path);
          char path3[100]="/home/bitcomm-06/Gstreamer/Videos/Cam2/";
          
       //   printf("array data is ==============================================%s",new_line[0]);
          strcat(path3,new_line[0]);
          strncpy(buff1,path3,strlen(path3)-1);
        //  printf("path3==============================================%s",path3);
         // printf("New path==============================================%s",buff1);
          strcat(buff1,"/");
          
          printf("After strcat path becomes====================================%s",buff1);
          char date[100]={0,};
         
          sprintf(date,"%s",MY_TIME);
          //g_print ("Datrshdgvjksfhnjkgvbjsfbgvkjbf--------- %s\n",date);
          strcat(date,".mp4");
         // g_print ("name-after strcpy--path3 date and time--------- %s\n",date);
          char path2[2000]={0,};
        //  strcat(path,filename);
          strcat(path2,buff1);
          strcat(path2,date);
          
        printf("Saving fine name is  path is ====================================%s",path2);
          // g_print ("name-after strcpy--path--------- %s\n",path);
         //  g_print ("name-after strcpy--path2--------- %s\n",path2);
          
         //  g_print ("#############@@@@@@@@@@@@@############@@@@@@@@#####--------- %s\n",path3);
       // char *token = strtok(filename, "/");
      //  char name[]="";
       
       // char name1[]="";
       // int i=0;
       // strcat(path,filename);
     //   g_print ("name-after strcpy--path--------- %s\n",path);
      //    while (token != NULL)
  //  {
        //printf("%s\n", token);
      
    //    strcat(name,token);
       //  strcat("/",name);
       
       
    //    g_print ("name-in strcpy----------- %s\n",token);
       
    //    token = strtok(NULL, "/");
    //    ++i;
   // }
   
    int value;
 
    // File name is changed here
   value = rename(path, path2);
 
    // Print the result
    if(!value)
    {
        printf("%s\n", "File name changed successfully");
    }
    else
    {
        perror("Error");
    }
 //  
  
   // rename("name  ");

       // g_print ("name-after strcpy--path--------- %s\n",path);
     
      ////  gst_structure_get_string (s, "index");
     //   gst_structure_get_clock_time (s,"timestamp",&timestamp);
       // g_print("timestamp: %llu \n", timestamp);
       
        //zeitgeist_timestamp_to_iso8601 (timestamp);
      //  zeitgeist_timestamp_to_timeval(timestamp,*result);
        // g_print ("timestamp------------ %s",&timestamp);
       // gst_structure_get_clock_time (s,"stream-time",&stream_time);
      //  g_print("stream_time: %llu \n", stream_time);
      //  gst_structure_get_clock_time (s,"running-time",&running_time);
      //  g_print("running_time: %llu \n", running_time);
      //  gst_structure_get_uint64(s, "offset", &offset);
      //  g_print("offset: %llu \n", offset);
      //  gst_structure_get_uint64(s, "offset-end", &offset_end);
      //  g_print("offset_end: %llu \n", offset_end);
         //gboolean fields=gst_structure_has_field(GstMultiFileSink,const gchar *filename);
       // gchar *zeitgeist_timestamp_to_iso8601 (timestamp);
         g_print("########################GST_MESSAGE_ELEMENT END CAM 2 #################\n");
    }
    break;



          //////END
        default:
          /* We should not reach here */
          //g_printerr ("Unexpected message received.\n");
          break;
      }
      gst_message_unref (msg);
    }
printf("value of terminate %d\n",terminate);
  } while (!terminate);

  gst_element_set_state (data.pipeline, GST_STATE_NULL);
  gst_object_unref (data.pipeline);
 gst_message_unref (msg);
  gst_object_unref (data.avenc);

camera2(NULL);
}

///////////////////////////////////////////////Cam 3//////////////////////////////////////////////////////////////////

  void * camera3(void * u)

  {
 

    printf("Thread starting....\n");
       // printf("%s",prop);
       //time_t t;
     //   srand((unsigned) time(&t));
        GstMessage *msg;
     
      //  time(&t);
        CustomData data;
        guint bus_watch_id;
        GstBus *bus;
        GstStateChangeReturn ret;
        gboolean terminate = FALSE;
        char cam2[9]="cam2";
        char num[256];
       // data.gchararray="Videos";
       // printf("%s",prop);
      
         /* Create the elements */
    //int oldstate,oldtype;
         //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
        data.source = gst_element_factory_make ("uridecodebin", "source");
        data.convert = gst_element_factory_make ("videoconvert", "convert");
        data.sink = gst_element_factory_make ("autovideosink", "sink");
        data.videoconvert1 = gst_element_factory_make("videoconvert", "videoconvert1");
    data.videoconvert2 = gst_element_factory_make("videoconvert", "videoconvert2");
    data.queue1 = gst_element_factory_make("queue", "queue1");
    data.queue2 = gst_element_factory_make("queue", "queue2");
    data.tee = gst_element_factory_make("tee", "tee");
  
    data.frameratefilter = gst_element_factory_make("capsfilter", NULL);
    data.videorate = gst_element_factory_make("videorate", NULL);
    data.avenc = gst_element_factory_make("avenc_mpeg2video", NULL);
    data.avimux = gst_element_factory_make("avimux", NULL);
    data.filesink = gst_element_factory_make("multifilesink", "filesink");
   // data.splitmuxsink = gst_element_factory_make("splitmuxsink", "splitmuxsink");
      //  data.getchararray = gst_element_factory_make("/home/shubham/splintng/Videos", "getchararray");

       // data.filesink2 = gst_element_factory_make("filesink2", NULL);
  

     /* Create the empty pipeline */
       data.pipeline = gst_pipeline_new ("test-pipeline");

  if (!data.pipeline || !data.source || !data.convert || !data.videoconvert1 || !data.videoconvert2 || !data.queue1 || !data.queue2 || !data.tee || !data.sink || !data.filesink  ) {
    g_printerr ("Not all elements could be created.\n");
    return 0;
  }
     //    g_object_set(G_OBJECT (data.filesink), "name", ctime(&t),"async",0, NULL);
        g_object_set(G_OBJECT(data.frameratefilter), "caps", gst_caps_from_string("video/x-raw,framerate=50/1"), NULL);
       //
  
     
       // g_object_set(G_OBJECT(data.filesink2), "location", strcat(cam22,ctime(&t)), "async", 0, NULL);
  
       // g_object_set(data.avenc, "bitrate", 4096, NULL);

  /* Build the pipeline. Note that we are NOT linking the source at this
   * point. We will do it later. */
  gst_bin_add_many (GST_BIN (data.pipeline), data.source, data.convert , data.videoconvert1, data.videoconvert2, data.queue1, data.queue2, data.tee, data.sink, data.frameratefilter, data.videorate, data.avenc, data.avimux, data.filesink,data.filesink2,NULL);
  if (!gst_element_link (data.convert, data.tee)) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
if (!gst_element_link_many(data.queue1, data.videoconvert1, data.sink, NULL))
        g_error("Failed to link display elements!");
    if (!gst_element_link_many(data.queue2, data.videorate, data.frameratefilter, data.videoconvert2, data.avenc,data.avimux, data.filesink, NULL))
        g_error("Failed to link save elements!");

    if ( !(data.tee_src_pad_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (data.tee), "src_%u"))) {
      g_critical ("Unable to get pad template!");
      return 0;
     }

        data.qpad1 = gst_element_get_static_pad(data.queue1, "sink");
    data.qpad2 = gst_element_get_static_pad(data.queue2, "sink");
    data.teepad1 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue1 branch.\n", gst_pad_get_name (data.teepad1));
    data.teepad2 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue2 branch.\n", gst_pad_get_name (data.teepad2));

    if(!data.teepad1 || !data.teepad2 || !data.qpad1 || !data.qpad2){
        g_error("Creation of one tee pad failed.");
        return 0;
    }

    gst_pad_link (data.teepad1, data.qpad1);
    gst_pad_link (data.teepad2, data.qpad2);

    gst_object_unref (GST_OBJECT (data.qpad1));
    gst_object_unref (GST_OBJECT (data.qpad2));
    gst_object_unref (GST_OBJECT (data.teepad1));
    gst_object_unref (GST_OBJECT (data.teepad2));

       //uri = gst_filename_to_uri (message[6], NULL);
      

    // Output a dot file of the pipeline
    // Be sure to $ export GST_DEBUG_DUMP_DOT_DIR=/tmp
    // and run with the --gst-enable-gst-debug command line switch
    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(data.pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline_graph");
 
   printf("%s",message[6]+10);
   printf("%s",message[7]+10);

  /* Set the URI to play */
  g_object_set (data.source, "uri",message[6]+10, NULL);

  /* Connect to the pad-added signal */
  g_signal_connect (data.source, "pad-added", G_CALLBACK (pad_added_handler), &data);
  //printf("%s",*prop);
  /* Start playing */
  printf("start playing..\n");
  ret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
  
     char buff[150]; 
     char path[150]="//home//bitcomm-06//Gstreamer//Videos//Cam3//";  
   //  char path2[]="/home/bitcomm-31/Videos/";  
     strcat(path,new_line[0]);
     //strcat(path2,new_line[0]);
     printf("path1 data is s==============================================%s",path);
     //printf("path2 data is s==============================================%s",path2);          
     printf("Array data is s==============================================%s",new_line[0]);
     printf("Array data is s==============================================%s",new_line[1]);
     strncpy(buff, path, strlen(path)-1);
     strcat(buff,"//ReplacedByDate_Time%03d.mp4");
     printf("path==============================================%s\n",buff);
     
    // g_object_set(G_OBJECT (data.filesink),"location","fullpath/Cam1_%03d.mp4","async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"location",buff,"async",0, NULL);
    //g_object_set(G_OBJECT (data.filesink),"location",fullpath,"async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"post-messages", TRUE, "async", 0, NULL);   
    g_object_set(G_OBJECT (data.filesink),"next-file", 4,"async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-file-size", 1000000, "async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-files",5, "async", 0, NULL);


printf("Thread Start.. Listen to bus\n");

 /* Listen to the bus */
  bus = gst_element_get_bus (data.pipeline);
printf("Bus status fetched\n");
  do {
 
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
    GST_MESSAGE_ANY);
    //msg=GST_MESSAGE_EOS;
   printf("Enetring switch case\n");
    /* Parse message */
    if (msg != NULL) {
      GError *err;
      gchar *debug_info;
      printf("msg.type %u\n",GST_MESSAGE_TYPE (msg));
      switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_ERROR:
          gst_message_parse_error (msg, &err, &debug_info);
          g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
          g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
          g_clear_error (&err);
          g_free (debug_info);
          terminate = TRUE;
          char fileName[]="CameraThree";
          CameraRemovedAudioPlayer(fileName);
        
//parse_output2(camera3buffer);


          break;

        case GST_MESSAGE_EOS:
//parse_output2(buff3);
          g_print ("End-Of-Stream reached.\n");
          terminate = TRUE;
          
          break;
        case GST_MESSAGE_STATE_CHANGED:
          /* We are only interested in state-changed messages from the pipeline */
          if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
            g_print ("Pipeline state changed from %s to %s:\n",
                gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
          }
          break;
          //////START
          case GST_MESSAGE_UNKNOWN:
        g_print("GST_MESSAGE_UNKNOWN\n");
break;
//case GST_MESSAGE_ELEMENT:
//g_print("########################GST_MESSAGE_ELEMENT     START #################\n");
//g_message ("get message %s", gst_structure_get_name (gst_message_get_structure(msg)));
//g_print ("filenemae %d",gst_message_get_structure(msg))->index);
//g_print("########################GST_MESSAGE_ELEMENT     END  #################\n");
//break;

case GST_MESSAGE_ELEMENT:
       
     
        s = gst_message_get_structure (msg);
   if (gst_structure_has_name(s, "GstMultiFileSink"))
    {
   
         //time_t t = time(NULL);
        // struct tm *tm = localtime(&t);
        // printf("%s\n", asctime(tm));
    //==================================================date time spaceless====================\\
  
   
    
    //localtime() uses the time pointed by t ,
    // to fill a tm structure with the
    // values that represent the
    // corresponding local time.
    
     time_t t ;
     struct tm *tmp ;
  
     time( &t );

     tmp = localtime( &t );
     char str[20]={0,};
    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%c", tmp);
    //sprintf(str,%c,MY_TIME);
    printf("date and time-------------------------------------------------------------------------------------------%s\n", MY_TIME );
   
    int i=0, len, j;
	
	len=strlen(MY_TIME);
	for(i=0; i<len; i++)
	{
		if(MY_TIME[i]==' '|| MY_TIME[i]==':')
		{
			MY_TIME[i]='_';
		}
	}
    
  
   
     //==================================================date time spaceless====================\\
   
   
         g_print("########################GST_MESSAGE_ELEMENT START CAM 3#################\n");
         g_print("File written.\n");
         filename = gst_structure_get_string (s, "filename");
        // g_print ("filename------------ %s\n",filename);
          char path[1000]={0,};
          char buff1[150]={0,};
          sprintf(path,"%s",filename);
          printf("path---########----------%s\n",path);
           g_print ("name-after strcpy--path--------- %s\n",path);
          char path3[100]="/home/bitcomm-06/Gstreamer/Videos/Cam3/";
          
          printf("array data is ==============================================%s",new_line[0]);
          strcat(path3,new_line[0]);
          strncpy(buff1,path3,strlen(path3)-1);
          printf("path3==============================================%s",path3);
          printf("New path==============================================%s",buff1);
          strcat(buff1,"/");
          
          printf("After strcat path becomes====================================%s",buff1);
          char date[100]={0,};
         
          sprintf(date,"%s",MY_TIME);
          //g_print ("Datrshdgvjksfhnjkgvbjsfbgvkjbf--------- %s\n",date);
          strcat(date,".mp4");
         // g_print ("name-after strcpy--path3 date and time--------- %s\n",date);
          char path2[2000]={0,};
        //  strcat(path,filename);
          strcat(path2,buff1);
          strcat(path2,date);
          
        printf("Saving fine name is  path is ====================================%s",path2);
          // g_print ("name-after strcpy--path--------- %s\n",path);
         //  g_print ("name-after strcpy--path2--------- %s\n",path2);
          
         //  g_print ("#############@@@@@@@@@@@@@############@@@@@@@@#####--------- %s\n",path3);
       // char *token = strtok(filename, "/");
      //  char name[]="";
       
       // char name1[]="";
       // int i=0;
       // strcat(path,filename);
     //   g_print ("name-after strcpy--path--------- %s\n",path);
      //    while (token != NULL)
  //  {
        //printf("%s\n", token);
      
    //    strcat(name,token);
       //  strcat("/",name);
       
       
    //    g_print ("name-in strcpy----------- %s\n",token);
       
    //    token = strtok(NULL, "/");
    //    ++i;
   // }
   
    int value;
 
    // File name is changed here
   value = rename(path, path2);
 
    // Print the result
    if(!value)
    {
        printf("%s\n", "File name changed successfully");
    }
    else
    {
        perror("Error");
    }
 //  
  
   // rename("name  ");

       // g_print ("name-after strcpy--path--------- %s\n",path);
     
      ////  gst_structure_get_string (s, "index");
     //   gst_structure_get_clock_time (s,"timestamp",&timestamp);
       // g_print("timestamp: %llu \n", timestamp);
       
        //zeitgeist_timestamp_to_iso8601 (timestamp);
      //  zeitgeist_timestamp_to_timeval(timestamp,*result);
        // g_print ("timestamp------------ %s",&timestamp);
       // gst_structure_get_clock_time (s,"stream-time",&stream_time);
      //  g_print("stream_time: %llu \n", stream_time);
      //  gst_structure_get_clock_time (s,"running-time",&running_time);
      //  g_print("running_time: %llu \n", running_time);
      //  gst_structure_get_uint64(s, "offset", &offset);
      //  g_print("offset: %llu \n", offset);
      //  gst_structure_get_uint64(s, "offset-end", &offset_end);
      //  g_print("offset_end: %llu \n", offset_end);
         //gboolean fields=gst_structure_has_field(GstMultiFileSink,const gchar *filename);
       // gchar *zeitgeist_timestamp_to_iso8601 (timestamp);
         g_print("########################GST_MESSAGE_ELEMENT END CAM 3#################\n");
    }
    break;



          //////END
        default:
          /* We should not reach here */
          //g_printerr ("Unexpected message received.\n");
          break;
      }
      gst_message_unref (msg);
    }
printf("value of terminate %d\n",terminate);
  } while (!terminate);

  gst_element_set_state (data.pipeline, GST_STATE_NULL);
  gst_object_unref (data.pipeline);

return 0;
}
 


//////////////////////////////////////////////////////////CAM 4//////////////////////////////////////////////////////////////

  void * camera4(void * u)

  {
 

    printf("Thread starting....\n");
       // printf("%s",prop);
       //time_t t;
     //   srand((unsigned) time(&t));
        GstMessage *msg;
     
      //  time(&t);
        CustomData data;
        guint bus_watch_id;
        GstBus *bus;
        GstStateChangeReturn ret;
        gboolean terminate = FALSE;
        char cam2[9]="cam2";
        char num[256];
       // data.gchararray="Videos";
       // printf("%s",prop);
      
         /* Create the elements */
    //int oldstate,oldtype;
         //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
        data.source = gst_element_factory_make ("uridecodebin", "source");
        data.convert = gst_element_factory_make ("videoconvert", "convert");
        data.sink = gst_element_factory_make ("autovideosink", "sink");
        data.videoconvert1 = gst_element_factory_make("videoconvert", "videoconvert1");
    data.videoconvert2 = gst_element_factory_make("videoconvert", "videoconvert2");
    data.queue1 = gst_element_factory_make("queue", "queue1");
    data.queue2 = gst_element_factory_make("queue", "queue2");
    data.tee = gst_element_factory_make("tee", "tee");
  
    data.frameratefilter = gst_element_factory_make("capsfilter", NULL);
    data.videorate = gst_element_factory_make("videorate", NULL);
    data.avenc = gst_element_factory_make("avenc_mpeg2video", NULL);
    data.avimux = gst_element_factory_make("avimux", NULL);
    data.filesink = gst_element_factory_make("multifilesink", "filesink");
   // data.splitmuxsink = gst_element_factory_make("splitmuxsink", "splitmuxsink");
      //  data.getchararray = gst_element_factory_make("/home/shubham/splintng/Videos", "getchararray");

       // data.filesink2 = gst_element_factory_make("filesink2", NULL);
  

     /* Create the empty pipeline */
       data.pipeline = gst_pipeline_new ("test-pipeline");

  if (!data.pipeline || !data.source || !data.convert || !data.videoconvert1 || !data.videoconvert2 || !data.queue1 || !data.queue2 || !data.tee || !data.sink || !data.filesink  ) {
    g_printerr ("Not all elements could be created.\n");
    return 0;
  }
     //    g_object_set(G_OBJECT (data.filesink), "name", ctime(&t),"async",0, NULL);
        g_object_set(G_OBJECT(data.frameratefilter), "caps", gst_caps_from_string("video/x-raw,framerate=50/1"), NULL);
       //
  
     
       // g_object_set(G_OBJECT(data.filesink2), "location", strcat(cam22,ctime(&t)), "async", 0, NULL);
  
       // g_object_set(data.avenc, "bitrate", 4096, NULL);

  /* Build the pipeline. Note that we are NOT linking the source at this
   * point. We will do it later. */
  gst_bin_add_many (GST_BIN (data.pipeline), data.source, data.convert , data.videoconvert1, data.videoconvert2, data.queue1, data.queue2, data.tee, data.sink, data.frameratefilter, data.videorate, data.avenc, data.avimux, data.filesink,data.filesink2,NULL);
  if (!gst_element_link (data.convert, data.tee)) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
if (!gst_element_link_many(data.queue1, data.videoconvert1, data.sink, NULL))
        g_error("Failed to link display elements!");
    if (!gst_element_link_many(data.queue2, data.videorate, data.frameratefilter, data.videoconvert2, data.avenc,data.avimux, data.filesink, NULL))
        g_error("Failed to link save elements!");

    if ( !(data.tee_src_pad_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (data.tee), "src_%u"))) {
      g_critical ("Unable to get pad template!");
      return 0;
     }

        data.qpad1 = gst_element_get_static_pad(data.queue1, "sink");
    data.qpad2 = gst_element_get_static_pad(data.queue2, "sink");
    data.teepad1 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue1 branch.\n", gst_pad_get_name (data.teepad1));
    data.teepad2 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue2 branch.\n", gst_pad_get_name (data.teepad2));

    if(!data.teepad1 || !data.teepad2 || !data.qpad1 || !data.qpad2){
        g_error("Creation of one tee pad failed.");
        return 0;
    }

    gst_pad_link (data.teepad1, data.qpad1);
    gst_pad_link (data.teepad2, data.qpad2);

    gst_object_unref (GST_OBJECT (data.qpad1));
    gst_object_unref (GST_OBJECT (data.qpad2));
    gst_object_unref (GST_OBJECT (data.teepad1));
    gst_object_unref (GST_OBJECT (data.teepad2));

       //uri = gst_filename_to_uri (message[6], NULL);
      

    // Output a dot file of the pipeline
    // Be sure to $ export GST_DEBUG_DUMP_DOT_DIR=/tmp
    // and run with the --gst-enable-gst-debug command line switch
    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(data.pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline_graph");
 
   printf("%s",message[6]+10);
   printf("%s",message[7]+10);

  /* Set the URI to play */
  g_object_set (data.source, "uri",message[7]+10, NULL);

  /* Connect to the pad-added signal */
  g_signal_connect (data.source, "pad-added", G_CALLBACK (pad_added_handler), &data);
  //printf("%s",*prop);
  /* Start playing */
  printf("start playing..\n");
  ret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
  
     char buff[150]; 
     char path[150]="//home//bitcomm-06//Gstreamer//Videos//Cam4//";  
   //  char path2[]="/home/bitcomm-31/Videos/";  
     strcat(path,new_line[0]);
     //strcat(path2,new_line[0]);
     printf("path1 data is s==============================================%s",path);
     //printf("path2 data is s==============================================%s",path2);          
     printf("Array data is s==============================================%s",new_line[0]);
     printf("Array data is s==============================================%s",new_line[1]);
     strncpy(buff, path, strlen(path)-1);
     strcat(buff,"//ReplacedByDate_Time%03d.mp4");
     printf("path==============================================%s\n",buff);
     
    // g_object_set(G_OBJECT (data.filesink),"location","fullpath/Cam1_%03d.mp4","async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"location",buff,"async",0, NULL);
    //g_object_set(G_OBJECT (data.filesink),"location",fullpath,"async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"post-messages", TRUE, "async", 0, NULL);   
    g_object_set(G_OBJECT (data.filesink),"next-file", 4,"async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-file-size", 1000000, "async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-files",5, "async", 0, NULL);


printf("Thread Start.. Listen to bus\n");

 /* Listen to the bus */
  bus = gst_element_get_bus (data.pipeline);
printf("Bus status fetched\n");
  do {
 
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
    GST_MESSAGE_ANY);
    //msg=GST_MESSAGE_EOS;
   printf("Enetring switch case\n");
    /* Parse message */
    if (msg != NULL) {
      GError *err;
      gchar *debug_info;
      printf("msg.type %u\n",GST_MESSAGE_TYPE (msg));
      switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_ERROR:
          gst_message_parse_error (msg, &err, &debug_info);
          g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
          g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
          g_clear_error (&err);
          g_free (debug_info);
          terminate = TRUE;
char fileName[]="CameraFour";
CameraRemovedAudioPlayer(fileName);
//.parse_output2(camera4buffer);


          break;

        case GST_MESSAGE_EOS:
//parse_output2(buff3);
          g_print ("End-Of-Stream reached.\n");
          terminate = TRUE;
          
          break;
        case GST_MESSAGE_STATE_CHANGED:
          /* We are only interested in state-changed messages from the pipeline */
          if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
            g_print ("Pipeline state changed from %s to %s:\n",
                gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
          }
          break;
          //////START
          case GST_MESSAGE_UNKNOWN:
        g_print("GST_MESSAGE_UNKNOWN\n");
break;
//case GST_MESSAGE_ELEMENT:
//g_print("########################GST_MESSAGE_ELEMENT     START #################\n");
//g_message ("get message %s", gst_structure_get_name (gst_message_get_structure(msg)));
//g_print ("filenemae %d",gst_message_get_structure(msg))->index);
//g_print("########################GST_MESSAGE_ELEMENT     END  #################\n");
//break;

case GST_MESSAGE_ELEMENT:
       
     
        s = gst_message_get_structure (msg);
   if (gst_structure_has_name(s, "GstMultiFileSink"))
    {
   
         //time_t t = time(NULL);
        // struct tm *tm = localtime(&t);
        // printf("%s\n", asctime(tm));
    //==================================================date time spaceless====================\\
  
   
    
    //localtime() uses the time pointed by t ,
    // to fill a tm structure with the
    // values that represent the
    // corresponding local time.
    
     time_t t ;
     struct tm *tmp ;
  
     time( &t );

     tmp = localtime( &t );
     char str[20]={0,};
    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%c", tmp);
    //sprintf(str,%c,MY_TIME);
    printf("date and time-------------------------------------------------------------------------------------------%s\n", MY_TIME );
   
    int i=0, len, j;
	
	len=strlen(MY_TIME);
	for(i=0; i<len; i++)
	{
		if(MY_TIME[i]==' '|| MY_TIME[i]==':')
		{
			MY_TIME[i]='_';
		}
	}
    
  
   
     //==================================================date time spaceless====================\\
   
   
         g_print("########################GST_MESSAGE_ELEMENT START CAM 4#################\n");
         g_print("File written.\n");
         filename = gst_structure_get_string (s, "filename");
        // g_print ("filename------------ %s\n",filename);
          char path[1000]={0,};
          char buff1[150]={0,};
          sprintf(path,"%s",filename);
          printf("path---########----------%s\n",path);
           g_print ("name-after strcpy--path--------- %s\n",path);
          char path3[100]="/home/bitcomm-06/Gstreamer/Videos/Cam4/";
          
          printf("array data is ==============================================%s",new_line[0]);
          strcat(path3,new_line[0]);
          strncpy(buff1,path3,strlen(path3)-1);
          printf("path3==============================================%s",path3);
          printf("New path==============================================%s",buff1);
          strcat(buff1,"/");
          
          printf("After strcat path becomes====================================%s",buff1);
          char date[100]={0,};
         
          sprintf(date,"%s",MY_TIME);
          //g_print ("Datrshdgvjksfhnjkgvbjsfbgvkjbf--------- %s\n",date);
          strcat(date,".mp4");
         // g_print ("name-after strcpy--path3 date and time--------- %s\n",date);
          char path2[2000]={0,};
        //  strcat(path,filename);
          strcat(path2,buff1);
          strcat(path2,date);
          
        printf("Saving fine name is  path is ====================================%s",path2);
          // g_print ("name-after strcpy--path--------- %s\n",path);
         //  g_print ("name-after strcpy--path2--------- %s\n",path2);
          
         //  g_print ("#############@@@@@@@@@@@@@############@@@@@@@@#####--------- %s\n",path3);
       // char *token = strtok(filename, "/");
      //  char name[]="";
       
       // char name1[]="";
       // int i=0;
       // strcat(path,filename);
     //   g_print ("name-after strcpy--path--------- %s\n",path);
      //    while (token != NULL)
  //  {
        //printf("%s\n", token);
      
    //    strcat(name,token);
       //  strcat("/",name);
       
       
    //    g_print ("name-in strcpy----------- %s\n",token);
       
    //    token = strtok(NULL, "/");
    //    ++i;
   // }
   
    int value;
 
    // File name is changed here
   value = rename(path, path2);
 
    // Print the result
    if(!value)
    {
        printf("%s\n", "File name changed successfully");
    }
    else
    {
        perror("Error");
    }
 //  
  
   // rename("name  ");

       // g_print ("name-after strcpy--path--------- %s\n",path);
     
      ////  gst_structure_get_string (s, "index");
     //   gst_structure_get_clock_time (s,"timestamp",&timestamp);
       // g_print("timestamp: %llu \n", timestamp);
       
        //zeitgeist_timestamp_to_iso8601 (timestamp);
      //  zeitgeist_timestamp_to_timeval(timestamp,*result);
        // g_print ("timestamp------------ %s",&timestamp);
       // gst_structure_get_clock_time (s,"stream-time",&stream_time);
      //  g_print("stream_time: %llu \n", stream_time);
      //  gst_structure_get_clock_time (s,"running-time",&running_time);
      //  g_print("running_time: %llu \n", running_time);
      //  gst_structure_get_uint64(s, "offset", &offset);
      //  g_print("offset: %llu \n", offset);
      //  gst_structure_get_uint64(s, "offset-end", &offset_end);
      //  g_print("offset_end: %llu \n", offset_end);
         //gboolean fields=gst_structure_has_field(GstMultiFileSink,const gchar *filename);
       // gchar *zeitgeist_timestamp_to_iso8601 (timestamp);
         g_print("########################GST_MESSAGE_ELEMENT END CAM 4#################\n");
    }
    break;



          //////END
        default:
          /* We should not reach here */
          //g_printerr ("Unexpected message received.\n");
          break;
      }
      gst_message_unref (msg);
    }
printf("value of terminate %d\n",terminate);
  } while (!terminate);

  gst_element_set_state (data.pipeline, GST_STATE_NULL);
  gst_object_unref (data.pipeline);

return 0;
}

////////////////////////////////////////////////////CAM 5////////////////////////////////////////////////////////////////////

  void * camera5(void * u)

  {
 

    printf("Thread starting....\n");
       // printf("%s",prop);
       //time_t t;
     //   srand((unsigned) time(&t));
        GstMessage *msg;
     
      //  time(&t);
        CustomData data;
        guint bus_watch_id;
        GstBus *bus;
        GstStateChangeReturn ret;
        gboolean terminate = FALSE;
        char cam2[9]="cam2";
        char num[256];
       // data.gchararray="Videos";
       // printf("%s",prop);
      
         /* Create the elements */
    //int oldstate,oldtype;
         //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
        data.source = gst_element_factory_make ("uridecodebin", "source");
        data.convert = gst_element_factory_make ("videoconvert", "convert");
        data.sink = gst_element_factory_make ("autovideosink", "sink");
        data.videoconvert1 = gst_element_factory_make("videoconvert", "videoconvert1");
    data.videoconvert2 = gst_element_factory_make("videoconvert", "videoconvert2");
    data.queue1 = gst_element_factory_make("queue", "queue1");
    data.queue2 = gst_element_factory_make("queue", "queue2");
    data.tee = gst_element_factory_make("tee", "tee");
  
    data.frameratefilter = gst_element_factory_make("capsfilter", NULL);
    data.videorate = gst_element_factory_make("videorate", NULL);
    data.avenc = gst_element_factory_make("avenc_mpeg2video", NULL);
    data.avimux = gst_element_factory_make("avimux", NULL);
    data.filesink = gst_element_factory_make("multifilesink", "filesink");
   // data.splitmuxsink = gst_element_factory_make("splitmuxsink", "splitmuxsink");
      //  data.getchararray = gst_element_factory_make("/home/shubham/splintng/Videos", "getchararray");

       // data.filesink2 = gst_element_factory_make("filesink2", NULL);
  

     /* Create the empty pipeline */
       data.pipeline = gst_pipeline_new ("test-pipeline");

  if (!data.pipeline || !data.source || !data.convert || !data.videoconvert1 || !data.videoconvert2 || !data.queue1 || !data.queue2 || !data.tee || !data.sink || !data.filesink  ) {
    g_printerr ("Not all elements could be created.\n");
    return 0;
  }
     //    g_object_set(G_OBJECT (data.filesink), "name", ctime(&t),"async",0, NULL);
        g_object_set(G_OBJECT(data.frameratefilter), "caps", gst_caps_from_string("video/x-raw,framerate=50/1"), NULL);
       //
  
     
       // g_object_set(G_OBJECT(data.filesink2), "location", strcat(cam22,ctime(&t)), "async", 0, NULL);
  
       // g_object_set(data.avenc, "bitrate", 4096, NULL);

  /* Build the pipeline. Note that we are NOT linking the source at this
   * point. We will do it later. */
  gst_bin_add_many (GST_BIN (data.pipeline), data.source, data.convert , data.videoconvert1, data.videoconvert2, data.queue1, data.queue2, data.tee, data.sink, data.frameratefilter, data.videorate, data.avenc, data.avimux, data.filesink,data.filesink2,NULL);
  if (!gst_element_link (data.convert, data.tee)) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
if (!gst_element_link_many(data.queue1, data.videoconvert1, data.sink, NULL))
        g_error("Failed to link display elements!");
    if (!gst_element_link_many(data.queue2, data.videorate, data.frameratefilter, data.videoconvert2, data.avenc,data.avimux, data.filesink, NULL))
        g_error("Failed to link save elements!");

    if ( !(data.tee_src_pad_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (data.tee), "src_%u"))) {
      g_critical ("Unable to get pad template!");
      return 0;
     }

        data.qpad1 = gst_element_get_static_pad(data.queue1, "sink");
    data.qpad2 = gst_element_get_static_pad(data.queue2, "sink");
    data.teepad1 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue1 branch.\n", gst_pad_get_name (data.teepad1));
    data.teepad2 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue2 branch.\n", gst_pad_get_name (data.teepad2));

    if(!data.teepad1 || !data.teepad2 || !data.qpad1 || !data.qpad2){
        g_error("Creation of one tee pad failed.");
        return 0;
    }

    gst_pad_link (data.teepad1, data.qpad1);
    gst_pad_link (data.teepad2, data.qpad2);

    gst_object_unref (GST_OBJECT (data.qpad1));
    gst_object_unref (GST_OBJECT (data.qpad2));
    gst_object_unref (GST_OBJECT (data.teepad1));
    gst_object_unref (GST_OBJECT (data.teepad2));

       //uri = gst_filename_to_uri (message[6], NULL);
      

    // Output a dot file of the pipeline
    // Be sure to $ export GST_DEBUG_DUMP_DOT_DIR=/tmp
    // and run with the --gst-enable-gst-debug command line switch
    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(data.pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline_graph");
 
   printf("%s",message[6]+10);
   printf("%s",message[7]+10);

  /* Set the URI to play */
  g_object_set (data.source, "uri",message[6]+10, NULL);

  /* Connect to the pad-added signal */
  g_signal_connect (data.source, "pad-added", G_CALLBACK (pad_added_handler), &data);
  //printf("%s",*prop);
  /* Start playing */
  printf("start playing..\n");
  ret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
  
     char buff[150]; 
     char path[150]="//home//bitcomm-06//Gstreamer//Videos//Cam5//";  
   //  char path2[]="/home/bitcomm-31/Videos/";  
     strcat(path,new_line[0]);
     //strcat(path2,new_line[0]);
     printf("path1 data is s==============================================%s",path);
     //printf("path2 data is s==============================================%s",path2);          
     printf("Array data is s==============================================%s",new_line[0]);
     printf("Array data is s==============================================%s",new_line[1]);
     strncpy(buff, path, strlen(path)-1);
     strcat(buff,"//ReplacedByDate_Time%03d.mp4");
     printf("path==============================================%s\n",buff);
     
    // g_object_set(G_OBJECT (data.filesink),"location","fullpath/Cam1_%03d.mp4","async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"location",buff,"async",0, NULL);
    //g_object_set(G_OBJECT (data.filesink),"location",fullpath,"async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"post-messages", TRUE, "async", 0, NULL);   
    g_object_set(G_OBJECT (data.filesink),"next-file", 4,"async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-file-size", 1000000, "async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-files",5, "async", 0, NULL);


printf("Thread Start.. Listen to bus\n");

 /* Listen to the bus */
  bus = gst_element_get_bus (data.pipeline);
printf("Bus status fetched\n");
  do {
 
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
    GST_MESSAGE_ANY);
    //msg=GST_MESSAGE_EOS;
   printf("Enetring switch case\n");
    /* Parse message */
    if (msg != NULL) {
      GError *err;
      gchar *debug_info;
      printf("msg.type %u\n",GST_MESSAGE_TYPE (msg));
      switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_ERROR:
          gst_message_parse_error (msg, &err, &debug_info);
          g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
          g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
          g_clear_error (&err);
          g_free (debug_info);
          terminate = TRUE;


//parse_output2(camera5buffer);


          break;

        case GST_MESSAGE_EOS:
//parse_output2(buff3);
          g_print ("End-Of-Stream reached.\n");
          terminate = TRUE;
          
          break;
        case GST_MESSAGE_STATE_CHANGED:
          /* We are only interested in state-changed messages from the pipeline */
          if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
            g_print ("Pipeline state changed from %s to %s:\n",
                gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
          }
          break;
          //////START
          case GST_MESSAGE_UNKNOWN:
        g_print("GST_MESSAGE_UNKNOWN\n");
break;
//case GST_MESSAGE_ELEMENT:
//g_print("########################GST_MESSAGE_ELEMENT     START #################\n");
//g_message ("get message %s", gst_structure_get_name (gst_message_get_structure(msg)));
//g_print ("filenemae %d",gst_message_get_structure(msg))->index);
//g_print("########################GST_MESSAGE_ELEMENT     END  #################\n");
//break;

case GST_MESSAGE_ELEMENT:
       
     
        s = gst_message_get_structure (msg);
   if (gst_structure_has_name(s, "GstMultiFileSink"))
    {
   
         //time_t t = time(NULL);
        // struct tm *tm = localtime(&t);
        // printf("%s\n", asctime(tm));
    //==================================================date time spaceless====================\\
  
   
    
    //localtime() uses the time pointed by t ,
    // to fill a tm structure with the
    // values that represent the
    // corresponding local time.
    
     time_t t ;
     struct tm *tmp ;
  
     time( &t );

     tmp = localtime( &t );
     char str[20]={0,};
    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%c", tmp);
    //sprintf(str,%c,MY_TIME);
    printf("date and time-------------------------------------------------------------------------------------------%s\n", MY_TIME );
   
    int i=0, len, j;
	
	len=strlen(MY_TIME);
	for(i=0; i<len; i++)
	{
		if(MY_TIME[i]==' '|| MY_TIME[i]==':')
		{
			MY_TIME[i]='_';
		}
	}
    
  
   
     //==================================================date time spaceless====================\\
   
   
         g_print("########################GST_MESSAGE_ELEMENT START CAM 5 #################\n");
         g_print("File written.\n");
         filename = gst_structure_get_string (s, "filename");
        // g_print ("filename------------ %s\n",filename);
          char path[1000]={0,};
          char buff1[150]={0,};
          sprintf(path,"%s",filename);
          printf("path---########----------%s\n",path);
           g_print ("name-after strcpy--path--------- %s\n",path);
          char path3[100]="/home/bitcomm-06/Gstreamer/Videos/Cam5/";
          
          printf("array data is ==============================================%s",new_line[0]);
          strcat(path3,new_line[0]);
          strncpy(buff1,path3,strlen(path3)-1);
          printf("path3==============================================%s",path3);
          printf("New path==============================================%s",buff1);
          strcat(buff1,"/");
          
          printf("After strcat path becomes====================================%s",buff1);
          char date[100]={0,};
         
          sprintf(date,"%s",MY_TIME);
          //g_print ("Datrshdgvjksfhnjkgvbjsfbgvkjbf--------- %s\n",date);
          strcat(date,".mp4");
         // g_print ("name-after strcpy--path3 date and time--------- %s\n",date);
          char path2[2000]={0,};
        //  strcat(path,filename);
          strcat(path2,buff1);
          strcat(path2,date);
          
        printf("Saving fine name is  path is ====================================%s",path2);
          // g_print ("name-after strcpy--path--------- %s\n",path);
         //  g_print ("name-after strcpy--path2--------- %s\n",path2);
          
         //  g_print ("#############@@@@@@@@@@@@@############@@@@@@@@#####--------- %s\n",path3);
       // char *token = strtok(filename, "/");
      //  char name[]="";
       
       // char name1[]="";
       // int i=0;
       // strcat(path,filename);
     //   g_print ("name-after strcpy--path--------- %s\n",path);
      //    while (token != NULL)
  //  {
        //printf("%s\n", token);
      
    //    strcat(name,token);
       //  strcat("/",name);
       
       
    //    g_print ("name-in strcpy----------- %s\n",token);
       
    //    token = strtok(NULL, "/");
    //    ++i;
   // }
   
    int value;
 
    // File name is changed here
   value = rename(path, path2);
 
    // Print the result
    if(!value)
    {
        printf("%s\n", "File name changed successfully");
    }
    else
    {
        perror("Error");
    }
 //  
  
   // rename("name  ");

       // g_print ("name-after strcpy--path--------- %s\n",path);
     
      ////  gst_structure_get_string (s, "index");
     //   gst_structure_get_clock_time (s,"timestamp",&timestamp);
       // g_print("timestamp: %llu \n", timestamp);
       
        //zeitgeist_timestamp_to_iso8601 (timestamp);
      //  zeitgeist_timestamp_to_timeval(timestamp,*result);
        // g_print ("timestamp------------ %s",&timestamp);
       // gst_structure_get_clock_time (s,"stream-time",&stream_time);
      //  g_print("stream_time: %llu \n", stream_time);
      //  gst_structure_get_clock_time (s,"running-time",&running_time);
      //  g_print("running_time: %llu \n", running_time);
      //  gst_structure_get_uint64(s, "offset", &offset);
      //  g_print("offset: %llu \n", offset);
      //  gst_structure_get_uint64(s, "offset-end", &offset_end);
      //  g_print("offset_end: %llu \n", offset_end);
         //gboolean fields=gst_structure_has_field(GstMultiFileSink,const gchar *filename);
       // gchar *zeitgeist_timestamp_to_iso8601 (timestamp);
         g_print("########################GST_MESSAGE_ELEMENT END CAM 5 #################\n");
    }
    break;



          //////END
        default:
          /* We should not reach here */
          //g_printerr ("Unexpected message received.\n");
          break;
      }
      gst_message_unref (msg);
    }
printf("value of terminate %d\n",terminate);
  } while (!terminate);

  gst_element_set_state (data.pipeline, GST_STATE_NULL);
  gst_object_unref (data.pipeline);

return 0;
}



/////////////////////////////////////////////////////CAM 6///////////////////////////////////////////////////////////////////

  void * camera6(void * u)

  {
 

    printf("Thread starting....\n");
       // printf("%s",prop);
       //time_t t;
     //   srand((unsigned) time(&t));
        GstMessage *msg;
     
      //  time(&t);
        CustomData data;
        guint bus_watch_id;
        GstBus *bus;
        GstStateChangeReturn ret;
        gboolean terminate = FALSE;
        char cam2[9]="cam2";
        char num[256];
       // data.gchararray="Videos";
       // printf("%s",prop);
      
         /* Create the elements */
    //int oldstate,oldtype;
         //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
        data.source = gst_element_factory_make ("uridecodebin", "source");
        data.convert = gst_element_factory_make ("videoconvert", "convert");
        data.sink = gst_element_factory_make ("autovideosink", "sink");
        data.videoconvert1 = gst_element_factory_make("videoconvert", "videoconvert1");
    data.videoconvert2 = gst_element_factory_make("videoconvert", "videoconvert2");
    data.queue1 = gst_element_factory_make("queue", "queue1");
    data.queue2 = gst_element_factory_make("queue", "queue2");
    data.tee = gst_element_factory_make("tee", "tee");
  
    data.frameratefilter = gst_element_factory_make("capsfilter", NULL);
    data.videorate = gst_element_factory_make("videorate", NULL);
    data.avenc = gst_element_factory_make("avenc_mpeg2video", NULL);
    data.avimux = gst_element_factory_make("avimux", NULL);
    data.filesink = gst_element_factory_make("multifilesink", "filesink");
   // data.splitmuxsink = gst_element_factory_make("splitmuxsink", "splitmuxsink");
      //  data.getchararray = gst_element_factory_make("/home/shubham/splintng/Videos", "getchararray");

       // data.filesink2 = gst_element_factory_make("filesink2", NULL);
  

     /* Create the empty pipeline */
       data.pipeline = gst_pipeline_new ("test-pipeline");

  if (!data.pipeline || !data.source || !data.convert || !data.videoconvert1 || !data.videoconvert2 || !data.queue1 || !data.queue2 || !data.tee || !data.sink || !data.filesink  ) {
    g_printerr ("Not all elements could be created.\n");
    return 0;
  }
     //    g_object_set(G_OBJECT (data.filesink), "name", ctime(&t),"async",0, NULL);
        g_object_set(G_OBJECT(data.frameratefilter), "caps", gst_caps_from_string("video/x-raw,framerate=50/1"), NULL);
       //
  
     
       // g_object_set(G_OBJECT(data.filesink2), "location", strcat(cam22,ctime(&t)), "async", 0, NULL);
  
       // g_object_set(data.avenc, "bitrate", 4096, NULL);

  /* Build the pipeline. Note that we are NOT linking the source at this
   * point. We will do it later. */
  gst_bin_add_many (GST_BIN (data.pipeline), data.source, data.convert , data.videoconvert1, data.videoconvert2, data.queue1, data.queue2, data.tee, data.sink, data.frameratefilter, data.videorate, data.avenc, data.avimux, data.filesink,data.filesink2,NULL);
  if (!gst_element_link (data.convert, data.tee)) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
if (!gst_element_link_many(data.queue1, data.videoconvert1, data.sink, NULL))
        g_error("Failed to link display elements!");
    if (!gst_element_link_many(data.queue2, data.videorate, data.frameratefilter, data.videoconvert2, data.avenc,data.avimux, data.filesink, NULL))
        g_error("Failed to link save elements!");

    if ( !(data.tee_src_pad_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (data.tee), "src_%u"))) {
      g_critical ("Unable to get pad template!");
      return 0;
     }

        data.qpad1 = gst_element_get_static_pad(data.queue1, "sink");
    data.qpad2 = gst_element_get_static_pad(data.queue2, "sink");
    data.teepad1 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue1 branch.\n", gst_pad_get_name (data.teepad1));
    data.teepad2 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue2 branch.\n", gst_pad_get_name (data.teepad2));

    if(!data.teepad1 || !data.teepad2 || !data.qpad1 || !data.qpad2){
        g_error("Creation of one tee pad failed.");
        return 0;
    }

    gst_pad_link (data.teepad1, data.qpad1);
    gst_pad_link (data.teepad2, data.qpad2);

    gst_object_unref (GST_OBJECT (data.qpad1));
    gst_object_unref (GST_OBJECT (data.qpad2));
    gst_object_unref (GST_OBJECT (data.teepad1));
    gst_object_unref (GST_OBJECT (data.teepad2));

       //uri = gst_filename_to_uri (message[6], NULL);
      

    // Output a dot file of the pipeline
    // Be sure to $ export GST_DEBUG_DUMP_DOT_DIR=/tmp
    // and run with the --gst-enable-gst-debug command line switch
    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(data.pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline_graph");
 
   printf("%s",message[6]+10);
   printf("%s",message[7]+10);

  /* Set the URI to play */
  g_object_set (data.source, "uri",message[7]+10, NULL);

  /* Connect to the pad-added signal */
  g_signal_connect (data.source, "pad-added", G_CALLBACK (pad_added_handler), &data);
  //printf("%s",*prop);
  /* Start playing */
  printf("start playing..\n");
  ret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
  
     char buff[150]; 
     char path[150]="//home//bitcomm-06//Gstreamer//Videos//Cam6//";  
   //  char path2[]="/home/bitcomm-31/Videos/";  
     strcat(path,new_line[0]);
     //strcat(path2,new_line[0]);
     printf("path1 data is s==============================================%s",path);
     //printf("path2 data is s==============================================%s",path2);          
     printf("Array data is s==============================================%s",new_line[0]);
     printf("Array data is s==============================================%s",new_line[1]);
     strncpy(buff, path, strlen(path)-1);
     strcat(buff,"//ReplacedByDate_Time%03d.mp4");
     printf("path==============================================%s\n",buff);
     
    // g_object_set(G_OBJECT (data.filesink),"location","fullpath/Cam1_%03d.mp4","async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"location",buff,"async",0, NULL);
    //g_object_set(G_OBJECT (data.filesink),"location",fullpath,"async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"post-messages", TRUE, "async", 0, NULL);   
    g_object_set(G_OBJECT (data.filesink),"next-file", 4,"async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-file-size", 1000000, "async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-files",5, "async", 0, NULL);


printf("Thread Start.. Listen to bus\n");

 /* Listen to the bus */
  bus = gst_element_get_bus (data.pipeline);
printf("Bus status fetched\n");
  do {
 
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
    GST_MESSAGE_ANY);
    //msg=GST_MESSAGE_EOS;
   printf("Enetring switch case\n");
    /* Parse message */
    if (msg != NULL) {
      GError *err;
      gchar *debug_info;
      printf("msg.type %u\n",GST_MESSAGE_TYPE (msg));
      switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_ERROR:
          gst_message_parse_error (msg, &err, &debug_info);
          g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
          g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
          g_clear_error (&err);
          g_free (debug_info);
          terminate = TRUE;


//parse_output2(camera6buffer);


          break;

        case GST_MESSAGE_EOS:
//parse_output2(buff3);
          g_print ("End-Of-Stream reached.\n");
          terminate = TRUE;
          
          break;
        case GST_MESSAGE_STATE_CHANGED:
          /* We are only interested in state-changed messages from the pipeline */
          if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
            g_print ("Pipeline state changed from %s to %s:\n",
                gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
          }
          break;
          //////START
          case GST_MESSAGE_UNKNOWN:
        g_print("GST_MESSAGE_UNKNOWN\n");
break;
//case GST_MESSAGE_ELEMENT:
//g_print("########################GST_MESSAGE_ELEMENT     START #################\n");
//g_message ("get message %s", gst_structure_get_name (gst_message_get_structure(msg)));
//g_print ("filenemae %d",gst_message_get_structure(msg))->index);
//g_print("########################GST_MESSAGE_ELEMENT     END  #################\n");
//break;

case GST_MESSAGE_ELEMENT:
       
     
        s = gst_message_get_structure (msg);
   if (gst_structure_has_name(s, "GstMultiFileSink"))
    {
   
         //time_t t = time(NULL);
        // struct tm *tm = localtime(&t);
        // printf("%s\n", asctime(tm));
    //==================================================date time spaceless====================\\
  
   
    
    //localtime() uses the time pointed by t ,
    // to fill a tm structure with the
    // values that represent the
    // corresponding local time.
    
     time_t t ;
     struct tm *tmp ;
  
     time( &t );

     tmp = localtime( &t );
     char str[20]={0,};
    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%c", tmp);
    //sprintf(str,%c,MY_TIME);
    printf("date and time-------------------------------------------------------------------------------------------%s\n", MY_TIME );
   
    int i=0, len, j;
	
	len=strlen(MY_TIME);
	for(i=0; i<len; i++)
	{
		if(MY_TIME[i]==' '|| MY_TIME[i]==':')
		{
			MY_TIME[i]='_';
		}
	}
    
  
   
     //==================================================date time spaceless====================\\
   
   
         g_print("########################GST_MESSAGE_ELEMENT START CAM 6 #################\n");
         g_print("File written.\n");
         filename = gst_structure_get_string (s, "filename");
        // g_print ("filename------------ %s\n",filename);
          char path[1000]={0,};
          char buff1[150]={0,};
          sprintf(path,"%s",filename);
          printf("path---########----------%s\n",path);
           g_print ("name-after strcpy--path--------- %s\n",path);
          char path3[100]="/home/bitcomm-06/Gstreamer/Videos/Cam6/";
          
          printf("array data is ==============================================%s",new_line[0]);
          strcat(path3,new_line[0]);
          strncpy(buff1,path3,strlen(path3)-1);
          printf("path3==============================================%s",path3);
          printf("New path==============================================%s",buff1);
          strcat(buff1,"/");
          
          printf("After strcat path becomes====================================%s",buff1);
          char date[100]={0,};
         
          sprintf(date,"%s",MY_TIME);
          //g_print ("Datrshdgvjksfhnjkgvbjsfbgvkjbf--------- %s\n",date);
          strcat(date,".mp4");
         // g_print ("name-after strcpy--path3 date and time--------- %s\n",date);
          char path2[2000]={0,};
        //  strcat(path,filename);
          strcat(path2,buff1);
          strcat(path2,date);
          
        printf("Saving fine name is  path is ====================================%s",path2);
          // g_print ("name-after strcpy--path--------- %s\n",path);
         //  g_print ("name-after strcpy--path2--------- %s\n",path2);
          
         //  g_print ("#############@@@@@@@@@@@@@############@@@@@@@@#####--------- %s\n",path3);
       // char *token = strtok(filename, "/");
      //  char name[]="";
       
       // char name1[]="";
       // int i=0;
       // strcat(path,filename);
     //   g_print ("name-after strcpy--path--------- %s\n",path);
      //    while (token != NULL)
  //  {
        //printf("%s\n", token);
      
    //    strcat(name,token);
       //  strcat("/",name);
       
       
    //    g_print ("name-in strcpy----------- %s\n",token);
       
    //    token = strtok(NULL, "/");
    //    ++i;
   // }
   
    int value;
 
    // File name is changed here
   value = rename(path, path2);
 
    // Print the result
    if(!value)
    {
        printf("%s\n", "File name changed successfully");
    }
    else
    {
        perror("Error");
    }
 //  
  
   // rename("name  ");

       // g_print ("name-after strcpy--path--------- %s\n",path);
     
      ////  gst_structure_get_string (s, "index");
     //   gst_structure_get_clock_time (s,"timestamp",&timestamp);
       // g_print("timestamp: %llu \n", timestamp);
       
        //zeitgeist_timestamp_to_iso8601 (timestamp);
      //  zeitgeist_timestamp_to_timeval(timestamp,*result);
        // g_print ("timestamp------------ %s",&timestamp);
       // gst_structure_get_clock_time (s,"stream-time",&stream_time);
      //  g_print("stream_time: %llu \n", stream_time);
      //  gst_structure_get_clock_time (s,"running-time",&running_time);
      //  g_print("running_time: %llu \n", running_time);
      //  gst_structure_get_uint64(s, "offset", &offset);
      //  g_print("offset: %llu \n", offset);
      //  gst_structure_get_uint64(s, "offset-end", &offset_end);
      //  g_print("offset_end: %llu \n", offset_end);
         //gboolean fields=gst_structure_has_field(GstMultiFileSink,const gchar *filename);
       // gchar *zeitgeist_timestamp_to_iso8601 (timestamp);
         g_print("########################GST_MESSAGE_ELEMENT END CAM 6#################\n");
    }
    break;



          //////END
        default:
          /* We should not reach here */
          //g_printerr ("Unexpected message received.\n");
          break;
      }
      gst_message_unref (msg);
    }
printf("value of terminate %d\n",terminate);
  } while (!terminate);

  gst_element_set_state (data.pipeline, GST_STATE_NULL);
  gst_object_unref (data.pipeline);

return 0;
}


//////////////////////////////////////////////////////CAM 7//////////////////////////////////////////////////////////////////

  void * camera7(void * u)

  {
 

    printf("Thread starting....\n");
       // printf("%s",prop);
       //time_t t;
     //   srand((unsigned) time(&t));
        GstMessage *msg;
     
      //  time(&t);
        CustomData data;
        guint bus_watch_id;
        GstBus *bus;
        GstStateChangeReturn ret;
        gboolean terminate = FALSE;
        char cam2[9]="cam2";
        char num[256];
       // data.gchararray="Videos";
       // printf("%s",prop);
      
         /* Create the elements */
    //int oldstate,oldtype;
         //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
        data.source = gst_element_factory_make ("uridecodebin", "source");
        data.convert = gst_element_factory_make ("videoconvert", "convert");
        data.sink = gst_element_factory_make ("autovideosink", "sink");
        data.videoconvert1 = gst_element_factory_make("videoconvert", "videoconvert1");
    data.videoconvert2 = gst_element_factory_make("videoconvert", "videoconvert2");
    data.queue1 = gst_element_factory_make("queue", "queue1");
    data.queue2 = gst_element_factory_make("queue", "queue2");
    data.tee = gst_element_factory_make("tee", "tee");
  
    data.frameratefilter = gst_element_factory_make("capsfilter", NULL);
    data.videorate = gst_element_factory_make("videorate", NULL);
    data.avenc = gst_element_factory_make("avenc_mpeg2video", NULL);
    data.avimux = gst_element_factory_make("avimux", NULL);
    data.filesink = gst_element_factory_make("multifilesink", "filesink");
   // data.splitmuxsink = gst_element_factory_make("splitmuxsink", "splitmuxsink");
      //  data.getchararray = gst_element_factory_make("/home/shubham/splintng/Videos", "getchararray");

       // data.filesink2 = gst_element_factory_make("filesink2", NULL);
  

     /* Create the empty pipeline */
       data.pipeline = gst_pipeline_new ("test-pipeline");

  if (!data.pipeline || !data.source || !data.convert || !data.videoconvert1 || !data.videoconvert2 || !data.queue1 || !data.queue2 || !data.tee || !data.sink || !data.filesink  ) {
    g_printerr ("Not all elements could be created.\n");
    return 0;
  }
     //    g_object_set(G_OBJECT (data.filesink), "name", ctime(&t),"async",0, NULL);
        g_object_set(G_OBJECT(data.frameratefilter), "caps", gst_caps_from_string("video/x-raw,framerate=50/1"), NULL);
       //
  
     
       // g_object_set(G_OBJECT(data.filesink2), "location", strcat(cam22,ctime(&t)), "async", 0, NULL);
  
       // g_object_set(data.avenc, "bitrate", 4096, NULL);

  /* Build the pipeline. Note that we are NOT linking the source at this
   * point. We will do it later. */
  gst_bin_add_many (GST_BIN (data.pipeline), data.source, data.convert , data.videoconvert1, data.videoconvert2, data.queue1, data.queue2, data.tee, data.sink, data.frameratefilter, data.videorate, data.avenc, data.avimux, data.filesink,data.filesink2,NULL);
  if (!gst_element_link (data.convert, data.tee)) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
if (!gst_element_link_many(data.queue1, data.videoconvert1, data.sink, NULL))
        g_error("Failed to link display elements!");
    if (!gst_element_link_many(data.queue2, data.videorate, data.frameratefilter, data.videoconvert2, data.avenc,data.avimux, data.filesink, NULL))
        g_error("Failed to link save elements!");

    if ( !(data.tee_src_pad_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (data.tee), "src_%u"))) {
      g_critical ("Unable to get pad template!");
      return 0;
     }

        data.qpad1 = gst_element_get_static_pad(data.queue1, "sink");
    data.qpad2 = gst_element_get_static_pad(data.queue2, "sink");
    data.teepad1 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue1 branch.\n", gst_pad_get_name (data.teepad1));
    data.teepad2 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue2 branch.\n", gst_pad_get_name (data.teepad2));

    if(!data.teepad1 || !data.teepad2 || !data.qpad1 || !data.qpad2){
        g_error("Creation of one tee pad failed.");
        return 0;
    }

    gst_pad_link (data.teepad1, data.qpad1);
    gst_pad_link (data.teepad2, data.qpad2);

    gst_object_unref (GST_OBJECT (data.qpad1));
    gst_object_unref (GST_OBJECT (data.qpad2));
    gst_object_unref (GST_OBJECT (data.teepad1));
    gst_object_unref (GST_OBJECT (data.teepad2));

       //uri = gst_filename_to_uri (message[6], NULL);
      

    // Output a dot file of the pipeline
    // Be sure to $ export GST_DEBUG_DUMP_DOT_DIR=/tmp
    // and run with the --gst-enable-gst-debug command line switch
    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(data.pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline_graph");
 
   printf("%s",message[6]+10);
   printf("%s",message[7]+10);

  /* Set the URI to play */
  g_object_set (data.source, "uri",message[6]+10, NULL);

  /* Connect to the pad-added signal */
  g_signal_connect (data.source, "pad-added", G_CALLBACK (pad_added_handler), &data);
  //printf("%s",*prop);
  /* Start playing */
  printf("start playing..\n");
  ret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
  
     char buff[150]; 
     char path[150]="//home//bitcomm-06//Gstreamer//Videos//Cam7//";  
   //  char path2[]="/home/bitcomm-31/Videos/";  
     strcat(path,new_line[0]);
     //strcat(path2,new_line[0]);
     printf("path1 data is s==============================================%s",path);
     //printf("path2 data is s==============================================%s",path2);          
     printf("Array data is s==============================================%s",new_line[0]);
char *CurrentDate=new_line[0];
     printf("Array data is s==============================================%s",new_line[1]);
     strncpy(buff, path, strlen(path)-1);
     strcat(buff,"//ReplacedByDate_Time%03d.mp4");
     printf("path==============================================%s\n",buff);
     
    // g_object_set(G_OBJECT (data.filesink),"location","fullpath/Cam1_%03d.mp4","async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"location",buff,"async",0, NULL);
    //g_object_set(G_OBJECT (data.filesink),"location",fullpath,"async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"post-messages", TRUE, "async", 0, NULL);   
    g_object_set(G_OBJECT (data.filesink),"next-file", 4,"async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-file-size", 1000000, "async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-files",5, "async", 0, NULL);


printf("Thread Start.. Listen to bus\n");

 /* Listen to the bus */
  bus = gst_element_get_bus (data.pipeline);
printf("Bus status fetched\n");
  do {
 
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
    GST_MESSAGE_ANY);
    //msg=GST_MESSAGE_EOS;
   printf("Enetring switch case\n");
    /* Parse message */
    if (msg != NULL) {
      GError *err;
      gchar *debug_info;
      printf("msg.type %u\n",GST_MESSAGE_TYPE (msg));
      switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_ERROR:
          gst_message_parse_error (msg, &err, &debug_info);
          g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
          g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
          g_clear_error (&err);
          g_free (debug_info);
          terminate = TRUE;


//parse_output2(camera7buffer);


          break;

        case GST_MESSAGE_EOS:
//parse_output2(buff3);
          g_print ("End-Of-Stream reached.\n");
          terminate = TRUE;
          
          break;
        case GST_MESSAGE_STATE_CHANGED:
          /* We are only interested in state-changed messages from the pipeline */
          if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
            g_print ("Pipeline state changed from %s to %s:\n",
                gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
          }
          break;
          //////START
          case GST_MESSAGE_UNKNOWN:
        g_print("GST_MESSAGE_UNKNOWN\n");
break;
//case GST_MESSAGE_ELEMENT:
//g_print("########################GST_MESSAGE_ELEMENT     START #################\n");
//g_message ("get message %s", gst_structure_get_name (gst_message_get_structure(msg)));
//g_print ("filenemae %d",gst_message_get_structure(msg))->index);
//g_print("########################GST_MESSAGE_ELEMENT     END  #################\n");
//break;

case GST_MESSAGE_ELEMENT:
       
     
        s = gst_message_get_structure (msg);
   if (gst_structure_has_name(s, "GstMultiFileSink"))
    {
   
         //time_t t = time(NULL);
        // struct tm *tm = localtime(&t);
        // printf("%s\n", asctime(tm));
    //==================================================date time spaceless====================\\
  
   
    
    //localtime() uses the time pointed by t ,
    // to fill a tm structure with the
    // values that represent the
    // corresponding local time.
    
     time_t t ;
     struct tm *tmp ;
  
     time( &t );

     tmp = localtime( &t );
     char str[20]={0,};
    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%c", tmp);
    //sprintf(str,%c,MY_TIME);
    printf("date and time-------------------------------------------------------------------------------------------%s\n", MY_TIME );
   
    int i=0, len, j;
	
	len=strlen(MY_TIME);
	for(i=0; i<len; i++)
	{
		if(MY_TIME[i]==' '|| MY_TIME[i]==':')
		{
			MY_TIME[i]='_';
		}
	}
    
  
   
     //==================================================date time spaceless====================\\
   
   
         g_print("########################GST_MESSAGE_ELEMENT START CAM 7 #################\n");
         g_print("File written.\n");
         filename = gst_structure_get_string (s, "filename");
        // g_print ("filename------------ %s\n",filename);
          char path[1000]={0,};
          char buff1[150]={0,};
          sprintf(path,"%s",filename);
          printf("path---########----------%s\n",path);
           g_print ("name-after strcpy--path--------- %s\n",path);
          char path3[100]="/home/bitcomm-06/Gstreamer/Videos/Cam7/";
          
          printf("array data is ==============================================%s",new_line[0]);
          strcat(path3,CurrentDate);
          strncpy(buff1,path3,strlen(path3)-1);
          printf("path3==============================================%s",path3);
          printf("New path==============================================%s",buff1);
          strcat(buff1,"/");
          
          printf("After strcat path becomes====================================%s",buff1);
          char date[100]={0,};
         
          sprintf(date,"%s",MY_TIME);
          //g_print ("Datrshdgvjksfhnjkgvbjsfbgvkjbf--------- %s\n",date);
          strcat(date,".mp4");
         // g_print ("name-after strcpy--path3 date and time--------- %s\n",date);
          char path2[2000]={0,};
        //  strcat(path,filename);
          strcat(path2,buff1);
          strcat(path2,date);
          
        printf("Saving fine name is  path is ====================================%s",path2);
          // g_print ("name-after strcpy--path--------- %s\n",path);
         //  g_print ("name-after strcpy--path2--------- %s\n",path2);
          
         //  g_print ("#############@@@@@@@@@@@@@############@@@@@@@@#####--------- %s\n",path3);
       // char *token = strtok(filename, "/");
      //  char name[]="";
       
       // char name1[]="";
       // int i=0;
       // strcat(path,filename);
     //   g_print ("name-after strcpy--path--------- %s\n",path);
      //    while (token != NULL)
  //  {
        //printf("%s\n", token);
      
    //    strcat(name,token);
       //  strcat("/",name);
       
       
    //    g_print ("name-in strcpy----------- %s\n",token);
       
    //    token = strtok(NULL, "/");
    //    ++i;
   // }
   
    int value;
 
    // File name is changed here
   value = rename(path, path2);
 
    // Print the result
    if(!value)
    {
        printf("%s\n", "File name changed successfully");
    }
    else
    {
        perror("Error");
    }
 //  
  
   // rename("name  ");

       // g_print ("name-after strcpy--path--------- %s\n",path);
     
      ////  gst_structure_get_string (s, "index");
     //   gst_structure_get_clock_time (s,"timestamp",&timestamp);
       // g_print("timestamp: %llu \n", timestamp);
       
        //zeitgeist_timestamp_to_iso8601 (timestamp);
      //  zeitgeist_timestamp_to_timeval(timestamp,*result);
        // g_print ("timestamp------------ %s",&timestamp);
       // gst_structure_get_clock_time (s,"stream-time",&stream_time);
      //  g_print("stream_time: %llu \n", stream_time);
      //  gst_structure_get_clock_time (s,"running-time",&running_time);
      //  g_print("running_time: %llu \n", running_time);
      //  gst_structure_get_uint64(s, "offset", &offset);
      //  g_print("offset: %llu \n", offset);
      //  gst_structure_get_uint64(s, "offset-end", &offset_end);
      //  g_print("offset_end: %llu \n", offset_end);
         //gboolean fields=gst_structure_has_field(GstMultiFileSink,const gchar *filename);
       // gchar *zeitgeist_timestamp_to_iso8601 (timestamp);
         g_print("########################GST_MESSAGE_ELEMENT END CAM 7#################\n");
    }
    break;



          //////END
        default:
          /* We should not reach here */
          //g_printerr ("Unexpected message received.\n");
          break;
      }
      gst_message_unref (msg);
    }
printf("value of terminate %d\n",terminate);
  } while (!terminate);

  gst_element_set_state (data.pipeline, GST_STATE_NULL);
  gst_object_unref (data.pipeline);

return 0;
}



//////////////////////////////////////////////////////CAM 8\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  void * camera8(void * u)

  {

    printf("Thread starting....\n");
       // printf("%s",prop);
       //time_t t;
     //   srand((unsigned) time(&t));
        GstMessage *msg;
     
      //  time(&t);
        CustomData data;
        guint bus_watch_id;
        GstBus *bus;
        GstStateChangeReturn ret;
        gboolean terminate = FALSE;
        char cam2[9]="cam2";
        char num[256];
       // data.gchararray="Videos";
       // printf("%s",prop);
      
         /* Create the elements */
    //int oldstate,oldtype;
         //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
        data.source = gst_element_factory_make ("uridecodebin", "source");
        data.convert = gst_element_factory_make ("videoconvert", "convert");
        data.sink = gst_element_factory_make ("autovideosink", "sink");
        data.videoconvert1 = gst_element_factory_make("videoconvert", "videoconvert1");
    data.videoconvert2 = gst_element_factory_make("videoconvert", "videoconvert2");
    data.queue1 = gst_element_factory_make("queue", "queue1");
    data.queue2 = gst_element_factory_make("queue", "queue2");
    data.tee = gst_element_factory_make("tee", "tee");
  
    data.frameratefilter = gst_element_factory_make("capsfilter", NULL);
    data.videorate = gst_element_factory_make("videorate", NULL);
    data.avenc = gst_element_factory_make("avenc_mpeg2video", NULL);
    data.avimux = gst_element_factory_make("avimux", NULL);
    data.filesink = gst_element_factory_make("multifilesink", "filesink");
   // data.splitmuxsink = gst_element_factory_make("splitmuxsink", "splitmuxsink");
      //  data.getchararray = gst_element_factory_make("/home/shubham/splintng/Videos", "getchararray");

       // data.filesink2 = gst_element_factory_make("filesink2", NULL);
  

     /* Create the empty pipeline */
       data.pipeline = gst_pipeline_new ("test-pipeline");

  if (!data.pipeline || !data.source || !data.convert || !data.videoconvert1 || !data.videoconvert2 || !data.queue1 || !data.queue2 || !data.tee || !data.sink || !data.filesink  ) {
    g_printerr ("Not all elements could be created.\n");
    return 0;
  }
     //    g_object_set(G_OBJECT (data.filesink), "name", ctime(&t),"async",0, NULL);
        g_object_set(G_OBJECT(data.frameratefilter), "caps", gst_caps_from_string("video/x-raw,framerate=50/1"), NULL);
       //
  
     
       // g_object_set(G_OBJECT(data.filesink2), "location", strcat(cam22,ctime(&t)), "async", 0, NULL);
  
       // g_object_set(data.avenc, "bitrate", 4096, NULL);

  /* Build the pipeline. Note that we are NOT linking the source at this
   * point. We will do it later. */
  gst_bin_add_many (GST_BIN (data.pipeline), data.source, data.convert , data.videoconvert1, data.videoconvert2, data.queue1, data.queue2, data.tee, data.sink, data.frameratefilter, data.videorate, data.avenc, data.avimux, data.filesink,data.filesink2,NULL);
  if (!gst_element_link (data.convert, data.tee)) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
if (!gst_element_link_many(data.queue1, data.videoconvert1, data.sink, NULL))
        g_error("Failed to link display elements!");
    if (!gst_element_link_many(data.queue2, data.videorate, data.frameratefilter, data.videoconvert2, data.avenc,data.avimux, data.filesink, NULL))
        g_error("Failed to link save elements!");

    if ( !(data.tee_src_pad_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (data.tee), "src_%u"))) {
      g_critical ("Unable to get pad template!");
      return 0;
     }

        data.qpad1 = gst_element_get_static_pad(data.queue1, "sink");
    data.qpad2 = gst_element_get_static_pad(data.queue2, "sink");
    data.teepad1 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue1 branch.\n", gst_pad_get_name (data.teepad1));
    data.teepad2 = gst_element_request_pad (data.tee, data.tee_src_pad_template, NULL, NULL);
    g_print ("Obtained request pad %s for queue2 branch.\n", gst_pad_get_name (data.teepad2));

    if(!data.teepad1 || !data.teepad2 || !data.qpad1 || !data.qpad2){
        g_error("Creation of one tee pad failed.");
        return 0;
    }

    gst_pad_link (data.teepad1, data.qpad1);
    gst_pad_link (data.teepad2, data.qpad2);

    gst_object_unref (GST_OBJECT (data.qpad1));
    gst_object_unref (GST_OBJECT (data.qpad2));
    gst_object_unref (GST_OBJECT (data.teepad1));
    gst_object_unref (GST_OBJECT (data.teepad2));

       //uri = gst_filename_to_uri (message[6], NULL);
      

    // Output a dot file of the pipeline
    // Be sure to $ export GST_DEBUG_DUMP_DOT_DIR=/tmp
    // and run with the --gst-enable-gst-debug command line switch
    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(data.pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline_graph");
 
   printf("%s",message[6]+10);
   printf("%s",message[7]+10);

  /* Set the URI to play */
  g_object_set (data.source, "uri",message[7]+10, NULL);

  /* Connect to the pad-added signal */
  g_signal_connect (data.source, "pad-added", G_CALLBACK (pad_added_handler), &data);
  //printf("%s",*prop);
  /* Start playing */
  printf("start playing..\n");
  ret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (data.pipeline);
    return 0;
  }
  
     char buff[150]; 
     char path[150]="//home//bitcomm-06//Gstreamer//Videos//Cam8//";  
   //  char path2[]="/home/bitcomm-31/Videos/";  
     strcat(path,new_line[0]);
     //strcat(path2,new_line[0]);
     printf("path1 data is s==============================================%s",path);
     //printf("path2 data is s==============================================%s",path2);          
     printf("Array data is s==============================================%s",new_line[0]);
     printf("Array data is s==============================================%s",new_line[1]);
     strncpy(buff, path, strlen(path)-1);
     strcat(buff,"//ReplacedByDate_Time%03d.mp4");
     printf("path==============================================%s\n",buff);
     
    // g_object_set(G_OBJECT (data.filesink),"location","fullpath/Cam1_%03d.mp4","async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"location",buff,"async",0, NULL);
    //g_object_set(G_OBJECT (data.filesink),"location",fullpath,"async",0, NULL);
    g_object_set(G_OBJECT (data.filesink),"post-messages", TRUE, "async", 0, NULL);   
    g_object_set(G_OBJECT (data.filesink),"next-file", 4,"async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-file-size", 1000000, "async", 0, NULL);
    g_object_set(G_OBJECT (data.filesink), "max-files",5, "async", 0, NULL);


printf("Thread Start.. Listen to bus\n");

 /* Listen to the bus */
  bus = gst_element_get_bus (data.pipeline);
printf("Bus status fetched\n");
  do {
 
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
    GST_MESSAGE_ANY);
    //msg=GST_MESSAGE_EOS;
   printf("Enetring switch case\n");
    /* Parse message */
    if (msg != NULL) {
      GError *err;
      gchar *debug_info;
      printf("msg.type %u\n",GST_MESSAGE_TYPE (msg));
      switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_ERROR:
          gst_message_parse_error (msg, &err, &debug_info);
          g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
          g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
          g_clear_error (&err);
          g_free (debug_info);
          terminate = TRUE;


//parse_output2(camera8buffer);


          break;

        case GST_MESSAGE_EOS:
//parse_output2(buff3);
          g_print ("End-Of-Stream reached.\n");
          terminate = TRUE;
          
          break;
        case GST_MESSAGE_STATE_CHANGED:
          /* We are only interested in state-changed messages from the pipeline */
          if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
            g_print ("Pipeline state changed from %s to %s:\n",
                gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
          }
          break;
          //////START
          case GST_MESSAGE_UNKNOWN:
        g_print("GST_MESSAGE_UNKNOWN\n");
break;
//case GST_MESSAGE_ELEMENT:
//g_print("########################GST_MESSAGE_ELEMENT     START #################\n");
//g_message ("get message %s", gst_structure_get_name (gst_message_get_structure(msg)));
//g_print ("filenemae %d",gst_message_get_structure(msg))->index);
//g_print("########################GST_MESSAGE_ELEMENT     END  #################\n");
//break;

case GST_MESSAGE_ELEMENT:
       
     
        s = gst_message_get_structure (msg);
   if (gst_structure_has_name(s, "GstMultiFileSink"))
    {
   
         //time_t t = time(NULL);
        // struct tm *tm = localtime(&t);
        // printf("%s\n", asctime(tm));
    //==================================================date time spaceless====================\\
  
   
    
    //localtime() uses the time pointed by t ,
    // to fill a tm structure with the
    // values that represent the
    // corresponding local time.
    
     time_t t ;
     struct tm *tmp ;
  
     time( &t );

     tmp = localtime( &t );
     char str[20]={0,};
    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%c", tmp);
    //sprintf(str,%c,MY_TIME);
    printf("date and time-------------------------------------------------------------------------------------------%s\n", MY_TIME );
   
    int i=0, len, j;
	
	len=strlen(MY_TIME);
	for(i=0; i<len; i++)
	{
		if(MY_TIME[i]==' '|| MY_TIME[i]==':')
		{
			MY_TIME[i]='_';
		}
	}
    
  
   
     //==================================================date time spaceless====================\\
   
   
         g_print("########################GST_MESSAGE_ELEMENT START CAM 8 #################\n");
         g_print("File written.\n");
         filename = gst_structure_get_string (s, "filename");
        // g_print ("filename------------ %s\n",filename);
          char path[1000]={0,};
          char buff1[150]={0,};
          sprintf(path,"%s",filename);
          printf("path---########----------%s\n",path);
           g_print ("name-after strcpy--path--------- %s\n",path);
          char path3[100]="/home/bitcomm-06/Gstreamer/Videos/Cam8/";
          
          printf("array data is ==============================================%s",new_line[0]);
          strcat(path3,new_line[0]);
          strncpy(buff1,path3,strlen(path3)-1);
          printf("path3==============================================%s",path3);
          printf("New path==============================================%s",buff1);
          strcat(buff1,"/");
          
          printf("After strcat path becomes====================================%s",buff1);
          char date[100]={0,};
         
          sprintf(date,"%s",MY_TIME);
          //g_print ("Datrshdgvjksfhnjkgvbjsfbgvkjbf--------- %s\n",date);
          strcat(date,".mp4");
         // g_print ("name-after strcpy--path3 date and time--------- %s\n",date);
          char path2[2000]={0,};
        //  strcat(path,filename);
          strcat(path2,buff1);
          strcat(path2,date);
          
        printf("Saving fine name is  path is ====================================%s",path2);
          // g_print ("name-after strcpy--path--------- %s\n",path);
         //  g_print ("name-after strcpy--path2--------- %s\n",path2);
          
         //  g_print ("#############@@@@@@@@@@@@@############@@@@@@@@#####--------- %s\n",path3);
       // char *token = strtok(filename, "/");
      //  char name[]="";
       
       // char name1[]="";
       // int i=0;
       // strcat(path,filename);
     //   g_print ("name-after strcpy--path--------- %s\n",path);
      //    while (token != NULL)
  //  {
        //printf("%s\n", token);
      
    //    strcat(name,token);
       //  strcat("/",name);
       
       
    //    g_print ("name-in strcpy----------- %s\n",token);
       
    //    token = strtok(NULL, "/");
    //    ++i;
   // }
   
    int value;
 
    // File name is changed here
   value = rename(path, path2);
 
    // Print the result
    if(!value)
    {
        printf("%s\n", "File name changed successfully");
    }
    else
    {
        perror("Error");
    }
 //  
  
   // rename("name  ");

       // g_print ("name-after strcpy--path--------- %s\n",path);
     
      ////  gst_structure_get_string (s, "index");
     //   gst_structure_get_clock_time (s,"timestamp",&timestamp);
       // g_print("timestamp: %llu \n", timestamp);
       
        //zeitgeist_timestamp_to_iso8601 (timestamp);
      //  zeitgeist_timestamp_to_timeval(timestamp,*result);
        // g_print ("timestamp------------ %s",&timestamp);
       // gst_structure_get_clock_time (s,"stream-time",&stream_time);
      //  g_print("stream_time: %llu \n", stream_time);
      //  gst_structure_get_clock_time (s,"running-time",&running_time);
      //  g_print("running_time: %llu \n", running_time);
      //  gst_structure_get_uint64(s, "offset", &offset);
      //  g_print("offset: %llu \n", offset);
      //  gst_structure_get_uint64(s, "offset-end", &offset_end);
      //  g_print("offset_end: %llu \n", offset_end);
         //gboolean fields=gst_structure_has_field(GstMultiFileSink,const gchar *filename);
       // gchar *zeitgeist_timestamp_to_iso8601 (timestamp);
         g_print("########################GST_MESSAGE_ELEMENT END CAM 8#################\n");
    }
    break;



          //////END
        default:
          /* We should not reach here */
          //g_printerr ("Unexpected message received.\n");
          break;
      }
      gst_message_unref (msg);
    }
printf("value of terminate %d\n",terminate);
  } while (!terminate);

  gst_element_set_state (data.pipeline, GST_STATE_NULL);
  gst_object_unref (data.pipeline);

return 0;
}



////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

/* This function will be called by the pad-added signal */
static void pad_added_handler (GstElement *src, GstPad *new_pad, CustomData *data) {
  GstPad *sink_pad = gst_element_get_static_pad (data->convert, "sink");
  GstPadLinkReturn ret;
  GstCaps *new_pad_caps = NULL;
  GstStructure *new_pad_struct = NULL;
  const gchar *new_pad_type = NULL;

  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  /* If our converter is already linked, we have nothing to do here */
  if (gst_pad_is_linked (sink_pad)) {
    g_print ("  We are already linked. Ignoring.\n");
    goto exit;
  }

  /* Check the new pad's type */
  new_pad_caps = gst_pad_query_caps (new_pad, NULL);
  new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
  new_pad_type = gst_structure_get_name (new_pad_struct);
  if (!g_str_has_prefix (new_pad_type, "video/x-raw")) {
    g_print ("  It has type '%s' which is not raw audio. Ignoring.\n", new_pad_type);
    goto exit;
  }


  /* Attempt the link */
  ret = gst_pad_link (new_pad, sink_pad);
  if (GST_PAD_LINK_FAILED (ret)) {
    g_print ("  Type is '%s' but link failed.\n", new_pad_type);
  } else {
    g_print ("  Link succeeded (type '%s').\n", new_pad_type);
  }

exit:
  /* Unreference the new pad's caps, if we got them */
  if (new_pad_caps != NULL)
    gst_caps_unref (new_pad_caps);

  /* Unreference the sink pad */
  gst_object_unref (sink_pad);
}
