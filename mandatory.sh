#!/bin/bash

echo "==================================================================="
valgrind --tool=helgrind ./philo 1 800 200 200
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes ./philo 1 800 200 200
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes --check-stack-refs=yes --fair-sched=yes ./philo 1 800 200 200
echo "==================================================================="
valgrind --tool=drd ./philo 1 800 200 200
echo "==================================================================="

valgrind --tool=helgrind ./philo 5 800 200 200
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes ./philo 5 800 200 200
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes --check-stack-refs=yes --fair-sched=yes ./philo 5 800 200 200
echo "==================================================================="
valgrind --tool=drd ./philo 5 800 200 200
echo "==================================================================="

valgrind --tool=helgrind ./philo 5 800 200 200 7
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes ./philo 5 800 200 200 7
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes --check-stack-refs=yes --fair-sched=yes ./philo 5 800 200 200 7
echo "==================================================================="
valgrind --tool=drd ./philo 5 800 200 200 7
echo "==================================================================="

valgrind --tool=helgrind ./philo 4 410 200 200
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes ./philo 4 410 200 200
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes --check-stack-refs=yes --fair-sched=yes ./philo 4 410 200 200
echo "==================================================================="
valgrind --tool=drd ./philo 4 410 200 200
echo "==================================================================="

valgrind --tool=helgrind ./philo 4 310 200 100
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes ./philo 4 310 200 100
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes --check-stack-refs=yes --fair-sched=yes ./philo 4 310 200 100
echo "==================================================================="
valgrind --tool=drd ./philo 4 310 200 100
echo "==================================================================="

valgrind --tool=helgrind ./philo 2 310 200 100
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes ./philo 2 310 200 100
echo "==================================================================="
valgrind --tool=helgrind --history-level=full --track-lockorders=yes --check-stack-refs=yes --fair-sched=yes ./philo 2 310 200 100
echo "==================================================================="
valgrind --tool=drd ./philo 2 310 200 100