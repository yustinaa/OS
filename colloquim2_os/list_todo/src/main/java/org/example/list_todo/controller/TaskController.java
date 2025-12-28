package org.example.list_todo.controller;

import org.example.list_todo.model.Task;
import org.springframework.web.bind.annotation.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicLong;

@RestController
@RequestMapping("/tasks")
public class TaskController {

    private List<Task> tasks = new ArrayList<>();
    private AtomicLong idCounter = new AtomicLong();

    @GetMapping
    public List<Task> getAllTasks() {
        return tasks;
    }

    @PostMapping
    public Task createTask(@RequestBody Task newTask) {
        newTask.setId(idCounter.incrementAndGet());
        tasks.add(newTask);
        return newTask;
    }

    // ПОЛУЧЕНИЕ ПО ID
    @GetMapping("/{id}")
    public Task getTask(@PathVariable Long id) {
        return tasks.stream()
                .filter(t -> t.getId().equals(id))
                .findFirst()
                .orElse(null); // Если не нашли, вернем пустоту (пока так)
    }
    @DeleteMapping("/{id}")
    public void deleteTask(@PathVariable Long id) {
        // Удаляем задачу, у которой ID совпадает с тем, что пришел в запросе
        tasks.removeIf(t -> t.getId().equals(id));
    }
}