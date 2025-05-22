from django.db import models

class User(models.Model):
    userid = models.AutoField(primary_key=True)
    username = models.CharField(max_length=50)
    password = models.CharField(max_length=256)
    name = models.CharField(max_length=50)
    surname = models.CharField(max_length=50)
    profilephoto = models.CharField(max_length=255, null=True, blank=True)
    online = models.BooleanField(default=False)
    accesstoken = models.CharField(max_length=255, null=True, blank=True)

    class Meta:
        managed = False
        db_table = 'User'


class Player(models.Model):
    playerid = models.AutoField(primary_key=True)
    userid = models.ForeignKey(User, on_delete=models.CASCADE, db_column='UserId')
    history = models.IntegerField(null=True, blank=True)
    score = models.IntegerField(null=True, blank=True)

    class Meta:
        managed = False
        db_table = 'Player'


class History(models.Model):
    historyid = models.AutoField(primary_key=True)
    datetime = models.DateTimeField()

    class Meta:
        managed = False
        db_table = 'History'


class Tournament(models.Model):
    tournamentid = models.AutoField(primary_key=True)
    style = models.CharField(max_length=50)

    class Meta:
        managed = False
        db_table = 'Tournament'


class TournamentPlayer(models.Model):
    tournamentplayerid = models.AutoField(primary_key=True)
    tournamentid = models.ForeignKey(Tournament, on_delete=models.CASCADE, db_column='TournamentId')
    userid = models.ForeignKey(User, on_delete=models.CASCADE, db_column='UserId')

    class Meta:
        managed = False
        db_table = 'TournamentPlayer'


class MatchSystem(models.Model):
    matchsystemid = models.AutoField(primary_key=True)
    style = models.CharField(max_length=50)

    class Meta:
        managed = False
        db_table = 'MatchSystem'


class TournamentMatch(models.Model):
    tournamentmatchid = models.AutoField(primary_key=True)
    tournamentid = models.ForeignKey(Tournament, on_delete=models.CASCADE, db_column='TournamentId')
    stage = models.CharField(max_length=50)

    class Meta:
        managed = False
        db_table = 'TournamentMatch'


class NormalMatch(models.Model):
    normalmatchid = models.AutoField(primary_key=True)

    class Meta:
        managed = False
        db_table = 'NormalMatch'


class MatchRelationship(models.Model):
    relationshipid = models.AutoField(primary_key=True)
    matchtype = models.CharField(max_length=50, choices=[('TournamentMatch', 'TournamentMatch'), ('NormalMatch', 'NormalMatch')])
    matchid = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'MatchRelationship'


class ChatType(models.Model):
    chattypeid = models.AutoField(primary_key=True)
    typename = models.CharField(max_length=50)

    class Meta:
        managed = False
        db_table = 'ChatType'


class Chat(models.Model):
    ChatId = models.AutoField(primary_key=True)
    ChatTypeId = models.ForeignKey(ChatType, on_delete=models.CASCADE, db_column='ChatTypeId')
    Name = models.CharField(max_length=255)

    class Meta:
        managed = False
        db_table = 'Chat'


class ChatUsers(models.Model):
    chatuserid = models.AutoField(primary_key=True)
    chatid = models.ForeignKey(Chat, on_delete=models.CASCADE, db_column='ChatId')
    userid = models.ForeignKey(User, on_delete=models.CASCADE, db_column='UserId')

    class Meta:
        managed = False
        db_table = 'ChatUsers'


class Message(models.Model):
    messageid = models.AutoField(primary_key=True)
    chatid = models.ForeignKey(Chat, on_delete=models.CASCADE, db_column='ChatId')
    content = models.TextField()
    senderuserid = models.ForeignKey(User, on_delete=models.CASCADE, db_column='SenderUserId')
    timestamp = models.DateTimeField()

    class Meta:
        managed = False
        db_table = 'Message'
