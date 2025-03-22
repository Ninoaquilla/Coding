using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.Json;
using System.Threading;

class TaskManager
{
    private List<TaskItem> tasks = new List<TaskItem>();
    private string filePath = "tasks.json";
    public event Action<string> TaskCompleted;

    public TaskManager() => LoadTasks();
    
    public void AddTask(string description)
    {
        var task = new TaskItem { Id = Guid.NewGuid(), Description = description, IsCompleted = false };
        tasks.Add(task);
        SaveTasks();
    }

    public void CompleteTask(Guid id)
    {
        var task = tasks.FirstOrDefault(t => t.Id == id);
        if (task != null)
        {
            task.IsCompleted = true;
            SaveTasks();
            TaskCompleted?.Invoke($"Task '{task.Description}' completed!");
        }
    }

    public void RemoveTask(Guid id)
    {
        tasks.RemoveAll(t => t.Id == id);
        SaveTasks();
    }

    public void ListTasks()
    {
        foreach (var task in tasks)
        {
            Console.WriteLine($"[{(task.IsCompleted ? "✔" : "✖")}] {task.Description} (ID: {task.Id})");
        }
    }
    
    private void SaveTasks() => File.WriteAllText(filePath, JsonSerializer.Serialize(tasks));
    private void LoadTasks()
    {
        if (File.Exists(filePath))
            tasks = JsonSerializer.Deserialize<List<TaskItem>>(File.ReadAllText(filePath)) ?? new List<TaskItem>();
    }
}

class TaskItem
{
    public Guid Id { get; set; }
    public string Description { get; set; }
    public bool IsCompleted { get; set; }
}

class Program
{
    static void Main()
    {
        TaskManager manager = new TaskManager();
        manager.TaskCompleted += message => Console.WriteLine("[EVENT] " + message);
        
        Thread backgroundTask = new Thread(() =>
        {
            while (true)
            {
                Thread.Sleep(5000);
                Console.WriteLine("[INFO] Background task running...");
            }
        }) { IsBackground = true };
        backgroundTask.Start();

        while (true)
        {
            Console.WriteLine("\n1. Add Task\n2. Complete Task\n3. Remove Task\n4. List Tasks\n5. Exit");
            Console.Write("Choose: ");
            var choice = Console.ReadLine();
            
            switch (choice)
            {
                case "1":
                    Console.Write("Enter task description: ");
                    manager.AddTask(Console.ReadLine());
                    break;
                case "2":
                    Console.Write("Enter task ID: ");
                    if (Guid.TryParse(Console.ReadLine(), out Guid completeId))
                        manager.CompleteTask(completeId);
                    break;
                case "3":
                    Console.Write("Enter task ID: ");
                    if (Guid.TryParse(Console.ReadLine(), out Guid removeId))
                        manager.RemoveTask(removeId);
                    break;
                case "4":
                    manager.ListTasks();
                    break;
                case "5":
                    return;
                default:
                    Console.WriteLine("Invalid choice.");
                    break;
            }
        }
    }
}
