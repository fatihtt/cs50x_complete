# Generated by Django 4.2 on 2023-04-08 06:44

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('english', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='wordimage',
            name='url',
            field=models.URLField(default=''),
            preserve_default=False,
        ),
    ]
