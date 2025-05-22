# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    dbUtils.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bortakuz <bortakuz@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 15:42:06 by bortakuz          #+#    #+#              #
#    Updated: 2025/01/07 20:33:34 by bortakuz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from django.http import JsonResponse
from django.db.models import Q
from UserManagement.models import Chat, Message
import json
from django.db import connection

from django.db import connection



def get_Global_Chat(limit_start):
    query = """
    SELECT "User"."Username", filtered_messages."Content", filtered_messages."TimeStamp"
    FROM (
        SELECT "Message"."SenderUserId","Message"."Content","Message"."TimeStamp" FROM "Message"
        WHERE "ChatId" = 1
        LIMIT 50
    ) AS filtered_messages
    INNER JOIN "User" ON filtered_messages."SenderUserId" = "User"."UserId"
    ORDER BY filtered_messages."TimeStamp" LIMIT 50;
    """
    try:
        with connection.cursor() as cursor:
            # Execute the query with the chat_id parameter
            cursor.execute(query)

            # Fetch the results
            rows = cursor.fetchall()

            # Get the column names
            columns = [col[0] for col in cursor.description]

            # Map the rows to column names
            data = [dict(zip(columns, row)) for row in rows]

        return data
    except Exception as e:
        return []

#def add_Global_Chat(message, userName):
    #Insert into "Message" ("ChatId", "SenderUserId", "Content") Values (1,(Select "UserId" from "User" where "UserId"=1 ),'Selam') 

def get_chat_messages(chat_id, limit_start):
    limit = limit_start -25
    if limit < 0:
        limit = 0
    query = """
    SELECT "User"."Username", filtered_messages."Content", filtered_messages."TimeStamp"
    FROM (
        SELECT "Message"."SenderUserId","Message"."Content","Message"."TimeStamp" FROM "Message"
        WHERE "ChatId" = %s
        LIMIT %s
    ) AS filtered_messages
    INNER JOIN "User" ON filtered_messages."SenderUserId" = "User"."UserId"
    ORDER BY filtered_messages."TimeStamp" LIMIT %s;
    """
    try:
        with connection.cursor() as cursor:
            # Execute the query with the chat_id parameter
            cursor.execute(query, (chat_id,limit,limit))

            # Fetch the results
            rows = cursor.fetchall()

            # Get the column names
            columns = [col[0] for col in cursor.description]

            # Map the rows to column names
            data = [dict(zip(columns, row)) for row in rows]

        return data
    except Exception as e:
        return []    
    
def add_message(message, room_name, user_name):
    try:
        with connection.cursor() as cursor:
            cursor.execute("""
                    INSERT INTO "Message" 
                    ("ChatId", "SenderUserId", "Content") 
                    VALUES ((SELECT "Chat"."ChatId" FROM "Chat" INNER JOIN "ChatType" 
                    WHERE "ChatTypeId"."TypeName"= %s), 
                    (SELECT "UserId" FROM "User" WHERE "Username" = %s), %s);"""
                    , (room_name, user_name, message))
            data = cursor.fetchall()
            if data:
                return 0
            else:
                return 1
    except Exception as e:
        return 3
    
def test():
    try:
        with connection.cursor() as cursor:
            cursor.execute('SELECT ChatId FROM CHAT')
            columns = [col[0] for col in cursor.description]  # Get column names
            rows = cursor.fetchall()
        data = [dict(zip(columns, row)) for row in rows]
        
        return data
    except Exception as e:
        return e

def addTest(message):
    try:
        with connection.cursor() as cursor:
            cursor.execute('INSERT INTO "Chat" ("ChatTypeId", "Name") VALUES (1, %s);', (message,))

        return True
    except Exception as e:
        return e