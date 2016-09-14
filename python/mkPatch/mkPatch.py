#!/bin//env python

######
# mkPatch.py
#
# Windows GUI for code review
######

# imports
import os
import re
import sys
import time
import Tkinter
import tkMessageBox

class DirStructure:
    def __init__(self):
        self.scriptDir = sys.path[0]
        self.tempDir = self.scriptDir + 'temp/'
        self.patchDir = self.scriptDir + 'patches/'
        self.logFile = None

    def checkStruct(self):
        if not os.path.exists(self.tempDir):
            os.mkdir(self.tempDir, 0755)
            print 'Temporary directory inexistent... now created'

        if not os.path.exists(self.patchDir):
            os.mkdir(self.patchDir)
            print 'Patch directory inexistent... now created'

    def openLog(self):
        self.logFile = open(self.tempDir + 'p4review.log', 'a')

    def closeLog(self):
        self.logFile.write('*' * 72 + '\n')
        self.logFile.close()

class Checks:
    def __init__(self, tempDir, guiWindow):
        self.tempDir = tempDir
        self.windowRef = guiWindow
        # Regex to find if the job exists
        self.re_FindJob = None
        self.jobName = None
        self.logFile = None

    def checkJob(self, jobName):
        self.jobName = jobName
        self.re_FindJob = re.compile('^' + self.jobName + '\s')
        os.system('p4 jobs > \"' + self.tempDir + 'p4_jobs.tmp\"')
        f_AllJobs = open(self.tempDir + 'p4_jobs.tmp')
        line = f_AllJobs.readline()
        while '' != line:
            genericMatch = self.re_FindJob.match(line)
            if None != genericMatch:
                break

            line = f_AllJobs.readline()

        f_AllJobs.close()
        if None == genericMatch:
            print 'This p4 job (' + self.jobName + ') does not exist'
            self.logFile.write('This p4 job (' + self.jobName + \
                ') does not exist\n')
            tkMessageBox.showerror(title='p4 job', \
                message='This p4 job (' + self.jobName + ') does not exist', \
                parent=self.windowRef)
            os.remove(self.tempDir + 'p4_jobs.tmp')
            return False
        else:
            print 'Job found'
            self.logFile.write('Job found\n')
            os.remove(self.tempDir + 'p4_jobs.tmp')
            return True

class P4Client:
    def __init__(self, tempDir, guiWindow):
        self.tempDir = tempDir
        self.windowRef = guiWindow
        # Finding client root
        self.re_ClientRoot = re.compile('^Root:\s*(.*)')
        self.re_GetClient = None
        self.selectedClient = None
        self.clientRoot = None
        self.logFile = None

    def testClient(self):
        # Find client in p4 clients
        self.re_GetClient = re.compile('^Client\s*' + self.selectedClient)
        print 'Trying to find the p4 client'
        self.logFile.write('Trying to find the p4 client\n')
        os.system('p4 clients > \"' + self.tempDir + 'p4_clients.tmp\"')
        f_P4Clients = open(self.tempDir + 'p4_clients.tmp')
        line = f_P4Clients.readline()
        while '' != line:
            clientMatch = self.re_GetClient.match(line)
            if None != clientMatch:
                break

            line = f_P4Clients.readline()

        f_P4Clients.close()
        os.remove(self.tempDir + 'p4_clients.tmp')
        if not clientMatch:
            print 'This p4 client does not exist'
            self.logFile.write('This p4 client does not exist\n')
            tkMessageBox.showerror(title='p4 client', \
                message='This p4 client (' + self.selectedClient + \
                    ') does not exist', \
                parent=self.windowRef)
            return False
        else:
            print 'Client found'
            self.logFile.write('Client found\n')
            return True

    def goToClientRoot(self):
        print 'Changing directory to the root of the selected p4 client'
        self.logFile.write(\
            'Changing directory to the root of the selected p4 client\n')
        os.system('p4 client -o ' + self.selectedClient + ' > \"' \
            + self.tempDir + 'client_spec.tmp\"')
        f_ClientSpec = open(self.tempDir + 'client_spec.tmp')
        line = f_ClientSpec.readline()
        while '' != line:
            genericMatch = self.re_ClientRoot.match(line)
            if None != genericMatch:
                self.clientRoot = genericMatch.group(1)
                break

            line = f_ClientSpec.readline()

        f_ClientSpec.close()
        os.remove(self.tempDir + 'client_spec.tmp')
        print 'Client root:', self.clientRoot
        self.logFile.write('Client root: ' + self.clientRoot + '\n')
        os.chdir(self.clientRoot)

    def testClientRoot(self):
        os.system('dir > zzz')
        print 'Made a file named \'zzz\' in the client root for testing purpose'

class ChangedFiles:
    def __init__(self, tempDir, patchDir, guiWindow):
        self.tempDir = tempDir
        self.patchDir = patchDir
        self.windowRef = guiWindow
        self.jobName = None
        self.usedClient = None
        self.logFile = None
        # List for changelists
        self.changeList = None
        # Regex to get the change number
        self.re_FindChange = re.compile('.*change\s*([0-9]*)\s*')
        # Lists for found files
        self.filesEdited = None
        self.filesAdded = None
        self.filesDeleted = None
        # Regex to find files
        self.re_EditType = re.compile('^([^#]*)#[0-9]*\s-\s([^\s]*)\s')
        # Pickup data about edited file
        self.re_EditFile = re.compile('^====\s*([^\s]*)\s-\s([^\s]*)')
        # Pickup data about file from p4 where
        self.re_WhereFile = re.compile('^([^-]\S+)\s\S+\s(\S+)')
        # Check if the line is a patch expeption
        self.re_patchException = re.compile('^[\+\-=][\+\-=]')
        # Output PatchFile
        self.f_PatchFile = None

    def pickupChangelists(self):
        print 'Tring to find all the changelists used by job', self.jobName
        self.logFile.write('Tring to find all the changelists used by job ' + \
            self.jobName + '\n')
        self.changeList = []
        os.system('p4 fixes -j ' + self.jobName + ' > \"' + self.tempDir \
            + 'p4_fixes.tmp\"')
        f_Fixes = open(self.tempDir + 'p4_fixes.tmp')
        line = f_Fixes.readline()
        while '' != line:
            genericMatch = self.re_FindChange.match(line)
            if None != genericMatch:
                self.changeList.append(genericMatch.group(1))

            line = f_Fixes.readline()

        f_Fixes.close()
        os.remove(self.tempDir + 'p4_fixes.tmp')
        if not len(self.changeList):
            print 'Unable to find changelists fixing to the job', self.jobName
            print 'Check if you are using this job for your project'
            print 'Unable to continue without changelists, aborting'
            self.logFile.write('Unable to find changelists fixing to the job ')
            self.logFile.write(self.jobName + '\n')
            self.logFile.write('Check if you are using this job for ' + \
                'your project\n')
            self.logFile.write('Unable to continue without changelists, ' + \
                'aborting\n')
            self.changeList = None
            tkMessageBox.showerror(title='p4 changelists', \
                message='Unable to find changelists fixing to the job' + \
                    self.jobName + \
                    '\nCheck if you are using this job for your project' + \
                    '\nUnable to continue without changelists, aborting', \
                parent=self.windowRef)
            return

        print 'Found Changelists'
        print 'Changelists', self.changeList
        self.logFile.write('Found Changelists\n')
        self.logFile.write('Changelists ' + str(self.changeList) + '\n')

    def pickupFiles(self):
        print 'Going to pickup all opened files on the client', self.usedClient
        print 'by the job', self.jobName
        self.logFile.write('Going to pickup all opened files on the client ' + \
            self.usedClient + '\n')
        self.logFile.write('by the job ' + self.jobName + '\n')
        if None == self.changeList:
            print 'Changelist where not found for this job, or where never'
            print 'searched, cannot continue without changelists, aborting'
            self.logFile.write('Changelist where not found for this job, ' + \
                'or where never\n')
            self.logFile.write('searched, cannot continue without ' + \
                'changelists, aborting')
            return

        self.filesEdited = []
        self.filesAdded = []
        self.filesDeleted = []
        for change in self.changeList:
            os.system('p4 -c ' + self.usedClient + ' opened -c ' + change + \
                ' > \"' + self.tempDir + 'opened_files.tmp\"' + ' 2>&1')
            f_OpenedFiles = open(self.tempDir + 'opened_files.tmp')
            line = f_OpenedFiles.readline()
            while '' != line:
                genericMatch = self.re_EditType.match(line)
                if None != genericMatch:
                    if 'edit' == genericMatch.group(2):
                        self.filesEdited.append(genericMatch.group(1))
                    elif 'add' == genericMatch.group(2):
                        self.filesAdded.append(genericMatch.group(1))
                    elif 'delete' == genericMatch.group(2):
                        self.filesDeleted.append(genericMatch.group(1))
                    elif 'integrate' == genericMatch.group(2):
                        self.filesEdited.append(genericMatch.group(1))
                    elif 'branch' == genericMatch.group(2):
                        self.filesAdded.append(genericMatch.group(1))

                line = f_OpenedFiles.readline()

            f_OpenedFiles.close()
            os.remove(self.tempDir + 'opened_files.tmp')

        if len(self.filesEdited):
            print 'Found edited / integrated files:'
            print self.filesEdited
            self.logFile.write('Found edited / integrated files:\n')
            self.logFile.write(str(self.filesEdited) + '\n')
        else:
            print 'No edited / integrated files on this job'
            self.logFile.write('No edited / integrated files on this job\n')
            self.filesEdited = None

        if len(self.filesAdded):
            print 'Found added / branched files:'
            print self.filesAdded
            self.logFile.write('Found added / branched files:\n')
            self.logFile.write(str(self.filesAdded) + '\n')
        else:
            print 'No added / branched files on this job'
            self.logFile.write('No added / branched files on this job\n')
            self.filesAdded = None

        if len(self.filesDeleted):
            print 'Found deleted files:'
            print self.filesDeleted
            self.logFile.write('Found deleted files:\n')
            self.logFile.write(str(self.filesDeleted) + '\n')
        else:
            print 'No deleted files on this job'
            self.logFile.write('No deleted files on this job\n')
            self.filesDeleted = None

    def processFiles(self):
        print 'Processing found files'
        self.logFile.write('Processing found files\n')
        doneSth = False
        self.f_PatchFile = open(self.patchDir + self.jobName + '.patch', 'w')
        if None != self.filesEdited:
            self.processEdit()
            doneSth = True

        if None != self.filesAdded:
            self.processAdd()
            doneSth = True

        if None != self.filesDeleted:
            self.processDelete()
            doneSth = True

        self.f_PatchFile.close()
        if doneSth:
            print 'Files processed into file ' + self.jobName + '.patch'
            self.logFile.write('Files processed into file ' + \
                 self.jobName + '.patch\n')
            return True
        else:
            print 'No files where found / processed!'
            print 'It may mean that you didn\'t linked the job with a change'
            self.logFile.write('No files where found / processed!\n')
            self.logFile.write('It may mean that you didn\'t ' + \
                'linked the job with a change\n')
            tkMessageBox.showerror(title='p4 opened files', \
                message='No files where found / processed!\n' + \
                    'It may mean that you didn\'t linked the correct job', \
                parent=self.windowRef)
            os.remove(self.patchDir + self.jobName + '.patch')
            return False

    def processEdit(self):
        print 'Processing edited / integrated files'
        self.logFile.write('Processing edited / integrated files\n')
        for file in self.filesEdited:
            print 'file:', file
            self.logFile.write('file: ' + str(file) + '\n')
            os.system('p4 -c ' + self.usedClient + ' diff -dU10000 ' + file + \
                ' > \"' + self.tempDir + 'edited_file.tmp')
            f_EditFile = open(self.tempDir + 'edited_file.tmp')
            line = f_EditFile.readline()
            self.f_PatchFile.write(line)
            fileNameMatch = self.re_EditFile.match(line)
            if None == fileNameMatch:
                print 'Application level error while processing an edited file'
                self.logFile.write('Application level error while ' + \
                    'processing an edited file\n')
                exit(1)

            # Create header lines
            self.f_PatchFile.write('--- ' + fileNameMatch.group(1) + '\n')
            self.f_PatchFile.write('+++ ' + fileNameMatch.group(2) + '\n')
            line = f_EditFile.readline()
            while '' != line:
                genericMatch = self.re_patchException.match(line)
                if None != genericMatch:
                    if '+' == line[0]:
                        self.f_PatchFile.write('+ ')
                        self.f_PatchFile.write(line[1:])
                    elif '-' == line[0]:
                        self.f_PatchFile.write('- ')
                        self.f_PatchFile.write(line[1:])
                    else:
                        self.f_PatchFile.write(' ')
                        self.f_PatchFile.write(line)

                else:
                    self.f_PatchFile.write(line)

                line = f_EditFile.readline()

            f_EditFile.close()
            os.remove(self.tempDir + 'edited_file.tmp')

    def processAdd(self):
        print 'Processing added / branched files'
        self.logFile.write('Processing added / branched files\n')
        for file in self.filesAdded:
            print 'file:', file
            self.logFile.write('file: ' +  str(file) + '\n')
            os.system('p4 -c ' + self.usedClient + ' where ' + file + \
                ' > \"' + self.tempDir + 'where.tmp\"')
            f_Where = open(self.tempDir + 'where.tmp')
            line = f_Where.readline()
            while '' != line:
                fileNameMatch = self.re_WhereFile.match(line)
                if None != fileNameMatch:
                    break

                line = f_Where.readline()

            f_Where.close()
            os.remove(self.tempDir + 'where.tmp')
            if None == fileNameMatch:
                print 'Application level error while processing an added file'
                self.logFile.write('Application level error while ' + \
                    'processing an added file\n')
                exit(1)

            # Create header lines
            self.f_PatchFile.write('==== ' + fileNameMatch.group(1) + ' - ' \
                + fileNameMatch.group(2) + ' ====\n')
            self.f_PatchFile.write('--- ' + fileNameMatch.group(1) + '\n')
            self.f_PatchFile.write('+++ ' + fileNameMatch.group(2) + '\n')
            f_AddedFile = open(fileNameMatch.group(2))
            lineCounter = 0
            line = f_AddedFile.readline()
            while '' != line:
                lineCounter += 1
                line = f_AddedFile.readline()

            f_AddedFile.close()
            self.f_PatchFile.write('@@ -1,' + str(lineCounter) + ' +1,' \
                + str(lineCounter) + ' @@\n')
            f_AddedFile = open(fileNameMatch.group(2))
            line = f_AddedFile.readline()
            while '' != line:
                genericMatch = self.re_patchException.match(line)
                if None != genericMatch:
                    self.f_PatchFile.write(' ')

                self.f_PatchFile.write('+' + line)
                line = f_AddedFile.readline()

            f_AddedFile.close()

    def processDelete(self):
        print 'Processing deleted files'
        self.logFile.write('Processing deleted files\n')
        for file in self.filesDeleted:
            print 'file:', file
            self.logFile.write('file: ' + str(file) + '\n')
            os.system('p4 -c ' + self.usedClient + ' where ' + file + \
                ' > \"' + self.tempDir + 'where.tmp\"')
            f_Where = open(self.tempDir + 'where.tmp')
            line = f_Where.readline()
            while '' != line:
                fileNameMatch = self.re_WhereFile.match(line)
                if None != fileNameMatch:
                    break

                line = f_Where.readline()

            f_Where.close()
            os.remove(self.tempDir + 'where.tmp')
            if None == fileNameMatch:
                print 'Application level error while processing a deleted file'
                self.logFile.write('Application level error while ' + \
                    'processing a deleted file')
                exit(1)

            # Create header lines
            self.f_PatchFile.write('==== ' + fileNameMatch.group(1) + ' - ' \
                + fileNameMatch.group(2) + ' ====\n')
            self.f_PatchFile.write('--- ' + fileNameMatch.group(1) + '\n')
            self.f_PatchFile.write('+++ ' + fileNameMatch.group(2) + '\n')
            os.system('p4 -c ' + self.usedClient + ' print -q ' + \
                fileNameMatch.group(1) + ' > \"' + self.tempDir + \
                'deleted_file.tmp\"')
            f_DeletedFile = open(self.tempDir + 'deleted_file.tmp')
            lineCounter = 0
            line = f_DeletedFile.readline()
            while '' != line:
                lineCounter += 1
                line = f_DeletedFile.readline()

            f_DeletedFile.close()
            self.f_PatchFile.write('@@ -1,' + str(lineCounter) + ' +1,' \
                + str(lineCounter) + ' @@\n')
            f_DeletedFile = open(self.tempDir + 'deleted_file.tmp')
            line = f_DeletedFile.readline()
            while '' != line:
                genericMatch = self.re_patchException.match(line)
                if None != genericMatch:
                    self.f_PatchFile.write(' ')

                self.f_PatchFile.write('-' + line)
                line = f_DeletedFile.readline()

            f_DeletedFile.close()
            os.remove(self.tempDir + 'deleted_file.tmp')

class ReviewGUI:
    def __init__(self):
        self.logFile = None
        self.rootWindow = Tkinter.Tk()
        self.rootWindow.title('p4 review')
        self.rootWindow.protocol('WM_DELETE_WINDOW', self.closingAll)

        # Toolbar
        self.upFrame = Tkinter.Frame(self.rootWindow)
        self.jobFrame = Tkinter.Frame(self.upFrame)
        self.jobLabel = Tkinter.Label(self.jobFrame, text='Job Name')
        self.jobEntry = Tkinter.Entry(self.jobFrame, width=18)
        self.jobLabel.pack(side='top', anchor='nw')
        self.jobEntry.pack(side='bottom')
        self.clientFrame = Tkinter.Frame(self.upFrame)
        self.clientLabel = Tkinter.Label(self.clientFrame, text='Client Name')
        self.clientEntry = Tkinter.Entry(self.clientFrame, width=30)
        self.clientLabel.pack(side='top', anchor='nw')
        self.clientEntry.pack(side='bottom', fill='x', expand=1)
        self.makePatch = Tkinter.Button(self.upFrame, text='Make Patch')
        self.jobFrame.pack(side='left')
        self.clientFrame.pack(side='left', fill='x', expand=1)
        self.makePatch.pack(side='right', anchor='se')
        self.upFrame.pack(side='top')

        # Statusbar
        self.downFrame = Tkinter.Frame(self.rootWindow)
        self.status = Tkinter.Label(self.downFrame, text='Select parameters')
        self.status.pack(side='left')
        self.downFrame.pack(side='bottom', fill='x')

    def closingAll(self):
        if None != self.logFile and not self.logFile.closed:
            self.logFile.write('*' * 20 + \
                ' Program / Log File Interrupted ' + '*' * 20 + '\n')
            self.logFile.close()

        self.rootWindow.destroy()

class P4Review:
    def __init__(self):
        self.dirStruct = DirStructure()
        self.dirStruct.checkStruct()
        self.window = ReviewGUI()
        self.check = Checks(self.dirStruct.tempDir, self.window.rootWindow)
        self.p4Client = P4Client(self.dirStruct.tempDir, self.window.rootWindow)
        self.changedFiles = ChangedFiles(self.dirStruct.tempDir, \
            self.dirStruct.patchDir, self.window.rootWindow)

    def runGUI(self):
        self.window.makePatch.config(command=self.wrapperPatch)
        self.window.jobEntry.bind('<Return>', self.eventPatch)
        self.window.clientEntry.bind('<Return>', self.eventPatch)
        self.window.rootWindow.mainloop()

    def eventPatch(self, event):
            self.wrapperPatch()

    def wrapperPatch(self):
        if '' == self.window.jobEntry.get():
            tkMessageBox.showerror(title='p4 review', \
                message='Job Name field (mandatory) is empty', \
                parent=self.window.rootWindow)
        elif '' == self.window.clientEntry.get():
            tkMessageBox.showerror(title='p4 review', \
                message='Client Name field (mandatory) is empty', \
                parent=self.window.rootWindow)
        else:
            self.makePatch()

    def makePatch(self):
        self.dirStruct.openLog()
        self.window.logFile = self.dirStruct.logFile
        print '*' * 26 + ' Starting new debug ' + '*' * 26
        self.dirStruct.logFile.write('*' * 26 + ' Starting new debug ' + \
            '*' * 26 + '\n')
        dateTime = time.localtime(time.time())
        print '*** %04d/%02d/%02d %02d:%02d:%02d ***' % (\
            dateTime.tm_year, dateTime.tm_mon, dateTime.tm_mday, \
            dateTime.tm_hour, dateTime.tm_min, dateTime.tm_sec)
        self.dirStruct.logFile.write('*** %04d/%02d/%02d %02d:%02d:%02d ***\n' \
            % (dateTime.tm_year, dateTime.tm_mon, dateTime.tm_mday, \
            dateTime.tm_hour, dateTime.tm_min, dateTime.tm_sec))
        self.window.status.config(text='Processing Job...')
        jobName = self.window.jobEntry.get()
        self.check.logFile = self.dirStruct.logFile
        if self.check.checkJob(jobName):
            self.window.status.config(text='Processing Client...')
            self.p4Client.selectedClient = self.window.clientEntry.get()
            self.p4Client.logFile = self.dirStruct.logFile
            if self.p4Client.testClient():
                self.p4Client.goToClientRoot()
                #self.p4Client.testClientRoot()
                self.window.status.config(text='Generating Patch File...')
                self.changedFiles.jobName = jobName
                self.changedFiles.logFile = self.dirStruct.logFile
                self.changedFiles.usedClient = self.p4Client.selectedClient
                self.changedFiles.pickupChangelists()
                self.changedFiles.pickupFiles()
                if self.changedFiles.processFiles():
                    statusMessage = 'Created patch file patch/' + jobName + \
                        '.patch'
                    self.window.status.config(text=statusMessage)

            else:
                self.window.status.config(text='Client not found, try again')

        else:
            self.window.status.config(text='No such p4 job, try again')

        self.dirStruct.closeLog()

####
# main
###

p4review = P4Review()
p4review.runGUI()

