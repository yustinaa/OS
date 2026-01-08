package org.example.list_todo.controller;

import org.example.list_todo.model.Task;
import org.example.list_todo.repository.TaskRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.server.ResponseStatusException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.List;

@RestController
@RequestMapping("/tasks")
public class TaskController {

    private static final Logger logger = LoggerFactory.getLogger(TaskController.class);
    @Autowired
    private TaskRepository taskRepository;

    @GetMapping
    public List<Task> getAllTasks() {
        logger.info("Вывод всех задач");
        return taskRepository.findAll();
    }

    @GetMapping("/{id}")
    public Task getTask(@PathVariable Long id) {
        logger.info("Поиск задачи с ID: {}", id);
        return taskRepository.findById(id)
                .orElseThrow(() -> {
                    logger.error("Задача с ID {} не найдена!", id);
                    return new ResponseStatusException(HttpStatus.NOT_FOUND, "Task not found");
                });
    }
    @PostMapping
    public Task createTask(@RequestBody Task newTask) {
        logger.info("Запрос на создание задачи: {}", newTask.getTitle());
        return taskRepository.save(newTask);
    }

    @DeleteMapping("/{id}")
    public void deleteTask(@PathVariable Long id) {
        logger.warn("Удаление задачи с ID: {}", id);
        taskRepository.deleteById(id);
    }

    @PatchMapping("/{id}")
    public Task updateTaskStatus(@PathVariable Long id, @RequestBody Task taskDetails) {
        logger.info("Поиск задачи с ID: {}", id);
        Task existingTask = taskRepository.findById(id)
                .orElseThrow(() -> {
                    logger.error("Задача с ID {} не найдена!", id);
                    return new ResponseStatusException(HttpStatus.NOT_FOUND, "Task not found");
                });
        existingTask.setStatus(taskDetails.getStatus());
        return taskRepository.save(existingTask);
    }
}