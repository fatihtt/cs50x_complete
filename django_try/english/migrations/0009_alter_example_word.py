# Generated by Django 4.2 on 2023-04-10 13:44

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('english', '0008_word_last_review_alter_learninglist_words'),
    ]

    operations = [
        migrations.AlterField(
            model_name='example',
            name='word',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='examples', to='english.word'),
        ),
    ]
