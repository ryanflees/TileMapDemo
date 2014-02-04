protoc -I=./ --cpp_out=./ ./netmsg.proto 

MACRO_PRE=MC_
MACRO_DEFINE=#define
OUTPUTFILE=RCMessage.h
PROTO_TEMP_FILE=proto_temp

grep -n //@@ netmsg.proto | cut -d':' -f1 > $PROTO_TEMP_FILE

> $OUTPUTFILE

echo "#ifndef __Minirpg_Message__">>$OUTPUTFILE
echo "#define __Minirpg_Message__">>$OUTPUTFILE

for line in `cat $PROTO_TEMP_FILE`
do {
	code=`awk "NR==$line" netmsg.proto`
	code=`echo $code | cut -d' ' -f2`
	newLine=$((line + 1))
	message=`awk "NR==$newLine" netmsg.proto`
	message=`echo $message | cut -d' ' -f2`
	message=`echo $message | tr '[a-z]' '[A-Z]'`
	define=`echo $message | sed 's/^/'$MACRO_DEFINE' '$MACRO_PRE'/g'`
	echo $define | sed 's/$/ '$code'/g' >> $OUTPUTFILE
}
done

echo "#endif">>$OUTPUTFILE

cat $OUTPUTFILE

rm $PROTO_TEMP_FILE
